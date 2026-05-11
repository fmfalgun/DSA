# Session 07 — Theory Reference
## D-Bus Signal Watching, pthreads, and Thread Lifecycle Management

---

## 0. Threads vs pthreads — The Doubt Cleared First

This is a common confusion. Here is the precise answer.

**A thread** is an abstract concept — an independent sequence of execution that shares memory with other threads in the same process. It is defined by the operating system, not by any library.

**pthreads** (POSIX Threads) is a *standard API* — a set of function signatures, types, and behaviors defined in IEEE POSIX 1003.1c — that lets you create and manage threads in C on any POSIX-compliant OS (Linux, macOS, BSD, etc.).

Think of it this way:

| Concept | Analogy |
|---------|---------|
| Thread | The idea of a "vehicle" |
| pthreads | The standardized steering wheel + pedal layout that all POSIX vehicles must follow |
| `libpthread` / kernel scheduler | The actual engine and wheels underneath |

When you call `pthread_create`, you are asking the OS kernel to create a real kernel-scheduled thread. The `pthread_*` functions are just a standardized C interface to the kernel's thread machinery. On Linux specifically, `pthread_create` internally calls `clone(2)` with flags like `CLONE_VM | CLONE_FILES | CLONE_SIGHAND` — meaning the new thread shares the address space, file descriptors, and signal handlers of the parent. That sharing is what distinguishes a thread from a process.

So: **threads are the thing, pthreads is the API you use to work with them in C.**

There are other threading APIs for other languages or systems — Windows has `CreateThread`, C11 has `<threads.h>`, C++ has `std::thread`. They all create real OS threads underneath; they differ only in interface.

---

## 1. The Problem: Method Calls vs Signals in D-Bus

In Session 06, the program called `GetManagedObjects` — a *method call*. The flow was:

```
your program  →  sends request message  →  BlueZ
your program  ←  receives reply message ←  BlueZ
```

This is synchronous: you ask, you wait, you get one reply, you're done. `dbus_connection_send_with_reply_and_block` handles this perfectly.

Script 2 needs something fundamentally different. You don't want to ask a question — you want to *listen* for events. When a device connects or disconnects, BlueZ *emits* a signal on the bus. No one asked for it; it just fires. Your program needs to be woken up when this happens.

This is the signal model:

```
BlueZ  →  emits PropertiesChanged signal  →  D-Bus bus
your program  ←  receives it (if subscribed)
```

There is no reply. There is no request. The signal is a one-way broadcast. `send_with_reply_and_block` will never see it — that function only handles replies to your own method calls.

---

## 2. The D-Bus Signal Reception Path

### 2.1 The Match Rule

D-Bus is a shared bus. Many processes are connected to it at once. To avoid every process receiving every message ever sent, D-Bus uses *match rules* — filters you register to tell the bus daemon which signals you care about.

You register a match rule with:

```c
dbus_bus_add_match(conn, rule_string, &err);
```

The rule string is a comma-separated list of key=value pairs:

```c
"type='signal',"
"sender='org.bluez',"
"interface='org.freedesktop.DBus.Properties',"
"member='PropertiesChanged'"
```

Breaking this down:

| Field | Value | Meaning |
|-------|-------|---------|
| `type` | `signal` | Only match signals, not method calls or replies |
| `sender` | `org.bluez` | Only signals from BlueZ |
| `interface` | `org.freedesktop.DBus.Properties` | The standard properties interface |
| `member` | `PropertiesChanged` | Specifically the PropertiesChanged signal |

After `dbus_bus_add_match`, the D-Bus daemon will start routing matching signals to your connection's incoming queue. Without a match rule, they are silently dropped.

You must also call `dbus_connection_flush(conn)` after adding the match rule to ensure the registration message is actually sent to the daemon before you start your dispatch loop.

### 2.2 The Dispatch Loop

Once signals are being routed to your connection, you need to *read* them. The correct function is:

```c
DBusMessage *msg = dbus_connection_pop_message(conn);
```

This does not block. If there is a message in the queue, it returns it. If there is nothing, it returns `NULL`. This is a non-blocking poll.

For a blocking wait — meaning your program sleeps until a signal arrives instead of spinning — you use:

```c
dbus_connection_read_write(conn, timeout_ms);
```

This tells D-Bus to read from the socket and populate the internal queue. It blocks for up to `timeout_ms` milliseconds waiting for data. After it returns, you call `dbus_connection_pop_message` to pull messages out one by one.

The standard dispatch loop pattern:

```c
while (1) {
    // Block up to 100ms, reading incoming data from socket into queue
    dbus_connection_read_write(conn, 100);

    // Pull one message off the queue
    DBusMessage *msg = dbus_connection_pop_message(conn);
    if (msg == NULL) continue;  // nothing yet, loop again

    // Check if it is the signal we care about
    if (dbus_message_is_signal(msg, 
            "org.freedesktop.DBus.Properties", 
            "PropertiesChanged")) {
        // handle it
    }

    dbus_message_unref(msg);  // always free the message
}
```

The `100` timeout means: if no data arrives in 100ms, unblock and let the loop spin. This keeps your program responsive — it can check other conditions between polls.

### 2.3 The PropertiesChanged Signal Structure

`PropertiesChanged` is defined in the `org.freedesktop.DBus.Properties` interface. When any BlueZ device property changes, BlueZ sends this signal on that device's object path.

The signal carries three arguments:

```
arg0: string        — interface name where the property lives
                      (e.g. "org.bluez.Device1")
arg1: dict{sv}      — dict of changed properties: name → variant value
                      (e.g. {"Connected": true, "RSSI": -72})
arg2: array{s}      — list of property names that were invalidated
                      (properties that changed but whose new value is not included)
```

The signal's *object path* (accessible via `dbus_message_get_path(msg)`) tells you *which device* sent it. For example: `/org/bluez/hci0/dev_AC_19_8E_D4_8A_95`.

So to detect a device connecting:
- Check `arg0 == "org.bluez.Device1"`
- Parse `arg1` dict for key `"Connected"` with value `true`
- Extract the device address from the object path

### 2.4 Why the Object Path Matters

BlueZ sends `PropertiesChanged` for *all* its managed objects — adapters, devices, services. Your match rule filters by interface and member, but multiple devices can change properties simultaneously. The object path is your only way to know *which* device's property changed. You extract it like:

```c
const char *path = dbus_message_get_path(msg);
// path = "/org/bluez/hci0/dev_AC_19_8E_D4_8A_95"
// Extract the address portion: "dev_AC_19_8E_D4_8A_95" → "AC:19:8E:D4:8A:95"
```

---

## 3. pthreads — API Reference for Script 2

### 3.1 Thread Lifecycle

A thread has a clear lifecycle:

```
pthread_create()  →  running (executes worker function)
                  →  returns from worker  →  joinable / zombie
pthread_join()    →  reaped (resources freed)

OR

pthread_cancel()  →  cancellation delivered at next cancellation point
                  →  thread exits
pthread_join()    →  reaped
```

Never `pthread_cancel` without `pthread_join`. The cancelled thread's resources (stack, thread descriptor) stay allocated until joined. This is the thread equivalent of a zombie process.

### 3.2 Key Functions

```c
#include <pthread.h>
// compile with: gcc ... -lpthread
```

**Creating a thread:**
```c
pthread_t tid;
int ret = pthread_create(&tid, NULL, worker_function, arg);
// Returns 0 on success, errno value on failure (does NOT set errno itself)
// arg is passed as the void* parameter to worker_function
```

**The worker function signature — always this exact form:**
```c
void *worker(void *arg) {
    // arg is whatever you passed to pthread_create
    // ...
    return NULL;  // or return a value, retrieved by pthread_join
}
```

**Waiting for a thread to finish:**
```c
pthread_join(tid, NULL);
// Blocks until the thread exits
// Second arg: pointer to receive the thread's return value (NULL to discard)
```

**Cancelling a thread from outside:**
```c
pthread_cancel(tid);
// Sends a cancellation request
// Thread exits at its next cancellation point (read, write, sleep, etc.)
// MUST still call pthread_join after this
```

**Making a thread cancellable (default is already DEFERRED):**
```c
// Inside the worker, set cancellation type:
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);   // accept cancellations (default)
pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);  // only at cancellation points (default)
```

**Manual cancellation point — insert one if your loop has no I/O:**
```c
pthread_testcancel();
// If a cancellation is pending, this causes the thread to exit here
// Use inside tight loops that don't call any I/O functions
```

### 3.3 Cancellation Points

Not every line of code is a valid place for a thread to be cancelled. The POSIX standard defines *cancellation points* — functions where the kernel is allowed to deliver a pending cancellation. These include: `sleep`, `nanosleep`, `read`, `write`, `recv`, `send`, `pthread_cond_wait`, and a few dozen others.

If your worker loop does nothing but compute (no I/O, no sleep), `pthread_cancel` will appear to have no effect until the loop incidentally hits one of those functions. The fix is to call `pthread_testcancel()` inside the loop — it is an explicit cancellation point.

```c
void *worker(void *arg) {
    char *address = (char *)arg;
    while (1) {
        printf("[%s] monitoring...\n", address);
        sleep(2);            // sleep is a cancellation point — cancel delivered here
        pthread_testcancel(); // explicit fallback if sleep is somehow skipped
    }
    return NULL;
}
```

### 3.4 Passing Arguments to Threads

`pthread_create` takes a single `void *` argument. For Script 2, you need to pass at minimum the device address. The correct approach is to pass a pointer to a struct or to a slot in your thread table.

**Wrong — passing a pointer to a local variable:**
```c
for (int i = 0; i < n; i++) {
    char *addr = devices[i].address;    // pointer to existing memory — fine
    pthread_create(&tid, NULL, worker, addr);
}
```
This is actually fine *if* `devices[i].address` lives long enough (global array does). What is wrong is passing a pointer to a loop variable:

```c
for (int i = 0; i < n; i++) {
    pthread_create(&tid, NULL, worker, &i);  // WRONG: &i is reused each iteration
}
```

By the time the thread reads `*arg`, `i` has already changed.

**Correct — pass a pointer to a stable location:**
```c
pthread_create(&tid, NULL, worker, thread_table[slot].address);
// thread_table is global — address is stable for the lifetime of the program
```

---

## 4. The Thread Table

Script 2 needs to track one thread per connected device. The natural structure is a fixed-size array of slots:

```c
#define MAX_DEVICES 32

typedef struct {
    char     address[18];   // device MAC address
    pthread_t tid;          // thread handle
    int      active;        // 1 = thread is running, 0 = slot is free
} ThreadSlot;

ThreadSlot thread_table[MAX_DEVICES];
int thread_table_count = 0;
```

**On connect event:**
1. Find a free slot (where `active == 0`)
2. Copy the device address into the slot
3. Set `active = 1`
4. Call `pthread_create` with the slot's address as arg

**On disconnect event:**
1. Find the slot with matching address (where `active == 1`)
2. Call `pthread_cancel(slot->tid)`
3. Call `pthread_join(slot->tid, NULL)`
4. Set `active = 0`

This is a simple but complete lifecycle management pattern. No dynamic allocation needed.

---

## 5. Full Architecture of Script 2

```
main()
  │
  ├── dbus_bus_add_match(PropertiesChanged, org.bluez)
  │
  └── dispatch loop:
        │
        ├── dbus_connection_read_write(conn, 100ms)
        │
        ├── dbus_connection_pop_message()
        │   returns NULL → continue
        │   returns msg →
        │     ├── check: is it PropertiesChanged?
        │     ├── parse arg0 → is it "org.bluez.Device1"?
        │     ├── parse arg1 → look for "Connected" key
        │     │   ├── value = TRUE:
        │     │   │     extract address from object path
        │     │   │     find free slot in thread_table
        │     │   │     pthread_create(worker, slot->address)
        │     │   │     slot->active = 1
        │     │   └── value = FALSE:
        │     │         find slot by address
        │     │         pthread_cancel(slot->tid)
        │     │         pthread_join(slot->tid, NULL)
        │     │         slot->active = 0
        │     └── dbus_message_unref(msg)
```

---

## 6. Key Facts to Internalize

| Question | Answer |
|----------|--------|
| What is a thread? | An OS-level execution unit sharing memory with its parent process |
| What is pthreads? | The POSIX C API for creating/managing threads — `pthread_create`, `pthread_join`, etc. |
| How does `pthread_create` work under the hood on Linux? | It calls `clone(2)` with `CLONE_VM \| CLONE_FILES \| CLONE_SIGHAND` |
| Why does `send_with_reply_and_block` not see signals? | It only reads replies to your own method calls; signals are broadcast, not replies |
| What does `dbus_bus_add_match` do? | Registers a filter with the daemon to route matching signals to your connection |
| What does `dbus_connection_read_write` do? | Blocks up to N ms waiting for data on the socket, then populates the internal queue |
| What does `dbus_connection_pop_message` do? | Non-blocking — removes and returns one message from the internal queue |
| What happens if you `pthread_cancel` without `pthread_join`? | The thread becomes a zombie — resources (stack, descriptor) are never freed |
| What is a cancellation point? | A function where a pending `pthread_cancel` is actually delivered (sleep, read, etc.) |
| What does `pthread_testcancel` do? | Acts as a manual cancellation point — forces delivery if cancellation is pending |
| How do you pass data to a thread? | Via the `void *arg` parameter of `pthread_create` — must point to stable memory |
