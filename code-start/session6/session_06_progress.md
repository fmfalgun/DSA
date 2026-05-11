# DSA / Systems Programming — Session 06 Progress Report

> **Goal:** Build Script 1 of a Bluetooth monitoring system — enumerate all nearby/known BT devices and extract their full configuration from the OS using D-Bus and BlueZ in C.
> **Language:** C
> **Approach:** Write independently, debug with minimal hints, understand *why* bugs are wrong.

---

## Overview

This session introduced a new practical track: a multi-script Bluetooth packet capture and anomaly detection system. The full system has 4 scripts:

| Script | Role |
|--------|------|
| 1 — lister | Enumerate BT devices and extract all config |
| 2 — orchestrator | Allocate/deallocate threads per device on connect/disconnect |
| 3 — capture | Capture BT packets per device into separate pcap files |
| 4 — analyzer | Analyze pcap files, flag anomalous packets |

**Session 06 covers Script 1 only.**

---

## Step 1 — Understanding the Stack

**Task:** Understand how BT device info flows from hardware to userspace.

### The Chain

```
Hardware (BT chip, hci0)
        ↓
Linux Kernel (HCI driver)
        ↓
BlueZ (bluetoothd — userspace BT daemon)
        ↓
D-Bus (IPC message bus)
        ↓
Your Program (queries D-Bus)
```

### Key Components

| Component | Role |
|-----------|------|
| BlueZ | The BT stack on all Linux distros — manages pairing, scanning, connections |
| D-Bus | Message passing system between processes — BlueZ publishes objects here |
| `org.bluez` | BlueZ's bus name — address on the D-Bus system bus |
| `GetManagedObjects` | Method on root object `/` — returns every object BlueZ manages |

### Raw Query

```bash
dbus-send --system --print-reply \
  --dest=org.bluez / \
  org.freedesktop.DBus.ObjectManager.GetManagedObjects
```

- `--system` — BlueZ lives on system bus, not session bus
- `/` — root object, only one that exposes ObjectManager
- Output: nested dict of object paths → interfaces → properties

### Output Structure

```
/org/bluez              ← BlueZ root (skip)
/org/bluez/hci0         ← local adapter
/org/bluez/hci0/dev_XX  ← external device (target)
```

---

## Step 2 — D-Bus in C

**Task:** Understand D-Bus API and write skeleton to get reply from BlueZ.

### Key Types

| Type | Purpose |
|------|---------|
| `DBusError` | Holds error info — must be initialized before use |
| `DBusConnection` | Open connection to the bus — like a socket |
| `DBusMessage` | One message — same type for requests and replies |
| `DBusMessageIter` | Cursor for walking message contents |
| `DBusBasicValue` | Union holding any primitive D-Bus value |

### Key Functions

```c
dbus_error_init(&err);                          // zero out error struct
dbus_bus_get(DBUS_BUS_SYSTEM, &err);            // connect to system bus
dbus_message_new_method_call(dest, path,        // build request message
    interface, method);
dbus_connection_send_with_reply_and_block(      // send and wait for reply
    conn, msg, -1, &err);
dbus_error_is_set(&err);                        // check if error occurred
dbus_message_iter_init(reply, &iter);           // start walking reply
dbus_message_iter_get_arg_type(&iter);          // what type is here?
dbus_message_iter_get_basic(&iter, &val);       // read primitive value
dbus_message_iter_recurse(&iter, &sub);         // go inside a container
dbus_message_iter_next(&iter);                  // move to next item
```

### Why DBusError needs init

C doesn't zero-initialize variables. Without `dbus_error_init`, `err.name` contains garbage — D-Bus can't distinguish "no error" from "error with garbage pointer". `dbus_error_init` sets `name = NULL` and `message = NULL` — then any non-NULL name means an error occurred.

### Why DBusBasicValue

Instead of declaring separate variables for each type (`uint32_t val`, `char *val`, `int val`), `DBusBasicValue` is a union that holds all primitive types. One variable, read the right field based on type:

```c
DBusBasicValue val;
dbus_message_iter_get_basic(&iter, &val);
if (type == 115) printf("%s", val.str);
if (type == 117) printf("%u", val.u32);
if (type == 98)  printf("%d", val.bool_val);
```

---

## Step 3 — Recursive Tree Walker

**Task:** Parse the nested D-Bus reply structure by recursively walking it.

### D-Bus Type Constants (ASCII values)

| Char | ASCII | Type |
|------|-------|------|
| `'a'` | 97 | Array (container) |
| `'e'` | 101 | Dict entry (container) |
| `'v'` | 118 | Variant (container) |
| `'s'` | 115 | String |
| `'o'` | 111 | Object path |
| `'b'` | 98 | Boolean |
| `'u'` | 117 | uint32 |
| `'n'` | 110 | int16 |
| `'y'` | 121 | Byte |
| `'q'` | 113 | uint16 |
| `0` | 0 | INVALID (end of level) |

### Walker Logic

```
walk(iter, level):
    while type != INVALID:
        if type is container (array/dict/variant):
            recurse into sub-iterator
            walk(sub, level+1)
        else:
            read value with get_basic
            process based on level
        next
```

### Level Map

| Level | Content |
|-------|---------|
| 2 | Object path (e.g. `/org/bluez/hci0/dev_XX`) |
| 4 | Interface name (e.g. `org.bluez.Device1`) |
| 6 | Property name (e.g. `Address`, `Connected`) |
| 7 | Property value (actual data) |
| 8 | Array item values (e.g. UUIDs) |

### Issues Faced & Resolutions

**Bug 1 — Infinite loop: type never updated**
- First attempt: got type before loop, never reassigned inside loop
- Root cause: `while(type != INVALID)` checks stale value — never exits
- Resolution: reassign `type = get_arg_type(&iter)` at end of each loop iteration

**Bug 2 — Double declaration shadows outer variable**
- Declared `int type` twice — once outside loop, once inside
- Inner declaration shadows outer — while condition always checked the outer stale value
- Resolution: declare `type` once, update it at end of loop

**Bug 3 — `get_basic` called on container types**
- Called `dbus_message_iter_get_basic` on arrays and dict entries
- D-Bus aborted: `"type array 97 not a basic type"`
- Resolution: only call `get_basic` in `else` branch — after confirming type is not a container

**Bug 4 — `dbus_message_iter_init` inside recursive function**
- Called `dbus_message_iter_init(reply, &iter)` at top of walker — even in recursive calls
- This reset iterator to top of reply on every recursion — infinite loop + SIGSEGV
- Resolution: call `dbus_message_iter_init` only once in `main`, pass iter by value to walker

**Bug 5 — `val.str` called on non-string types**
- At level 2, checked `strstr(val.str, "dev_")` without type guard
- If current item was a bool or uint32, `val.str` was garbage → SIGSEGV
- Resolution: added `&& (type == 111)` guard before calling `val.str`

---

## Step 4 — BT_NODE Struct

**Task:** Define a struct to store one device's extracted properties.

```c
struct BT_NODE {
    char     address[18];       // MAC: AA:BB:CC:DD:EE:FF + null
    char     address_type[8];   // "public" or "random"
    char     name[64];          // device display name
    char     alias[64];         // local alias
    uint32_t bt_class;          // device type bitmask (renamed from 'class' — C++ keyword)
    char     icon[32];          // BlueZ device type hint
    int      paired;            // pairing completed
    int      bonded;            // LTK stored
    int      trusted;           // auto-connect allowed
    int      blocked;           // blacklisted
    int      legacy_pairing;    // PIN-based vs SSP
    int      cable_pairing;
    int      connected;         // currently connected
    int      services_resolved; // GATT services discovered
    char     uuids[16][37];     // supported BT profiles (UUID strings)
    int      uuid_count;        // how many UUIDs filled
    char     adapter[32];       // owning adapter path
    int16_t  rssi;              // signal strength
    char     protocol[16];      // "BR/EDR", "BLE", "Dual"
};
```

### Key Decisions

- `class` renamed to `bt_class` — `class` is a reserved keyword in C++; future-proofing
- Fixed-size char arrays for all strings — no dynamic allocation needed; BlueZ paths are predictable lengths
- `uuids[16][37]` — max 16 UUIDs, each UUID is always 36 chars + null = 37
- `bool` not used — no `<stdbool.h>` needed; `int` with 0/1 works fine

---

## Step 5 — Struct Population via Walker

**Task:** Wire walker to fill `BT_NODE` structs using global context variables.

### Global State

```c
struct BT_NODE devices[32];   // all discovered devices
int devices_count = 0;        // how many found
char current_interface[64];   // which interface we're inside
char current_property[64];    // which property name was just read
```

### Population Logic

```
level 2 + type==object_path + contains "dev_" → devices_count++
level 4 + type==string → save to current_interface
         + value=="org.bluez.Bearer.BREDR1" → set protocol="BR/EDR"
level 6 + type==string → save to current_property
level 7 + current_interface=="org.bluez.Device1" → fill struct field by matching current_property
level 8 + current_interface=="org.bluez.Device1" + current_property=="UUIDs" → append to uuids[]
```

### Issues Faced & Resolutions

**Bug 1 — `current_interface = val.str` (array assignment)**
- Cannot assign directly to a `char[]` array in C
- Root cause: arrays are not assignable — only pointers are
- Resolution: use `strncpy(current_interface, val.str, sizeof(current_interface))`

**Bug 2 — Adapter data leaking into devices[0]**
- `current_interface` got set to `org.bluez.Adapter1` during adapter processing
- Level 7 had no interface filter — filled devices[0] with adapter's address/name
- Resolution: added `strcmp(current_interface, "org.bluez.Device1") == 0` guard at level 7 and 8

**Bug 3 — Off-by-one: devices_count incremented before data fills**
- `devices_count++` at level 2 makes count = 1 for first device
- Level 7 used `devices[devices_count]` = `devices[1]` — wrong slot
- `devices[0]` always empty
- Resolution: use `devices[devices_count - 1]` at levels 7 and 8

**Bug 4 — `temp` pointer uninitialized at level 8**
- `temp` declared as local variable inside walker
- Set at level 7 in one recursive call, but level 8 is a different call — different stack frame
- Root cause: recursive calls don't share local variables
- Resolution: set `temp = &devices[devices_count - 1]` at top of level 7 block; use `devices[devices_count-1]` directly at level 8

**Bug 5 — `uuid_count` used with `temp->uuid_count++` at level 8**
- `temp` not defined at level 8 scope
- Resolution: use `devices[devices_count-1].uuid_count` directly

**Bug 6 — `val.str` used without type check at levels 4 and 6**
- Not all items at those levels are strings — booleans and numbers also appear
- Calling `strncpy(..., val.str, ...)` on a non-string value → garbage or crash
- Resolution: added `(type == 115 || type == 111)` guard before copying

**Bug 7 — Protocol detection: `current_interface` overwritten after `org.bluez.Device1`**
- After Device1 properties, BlueZ sends `org.bluez.Bearer.BREDR1`, `org.bluez.MediaControl1` etc.
- `current_interface` kept being overwritten — UUIDs at level 8 lost their interface context
- Resolution: detect `BREDR1` at level 4 directly and set protocol field immediately

---

## Step 6 — Final Output

Script correctly enumerates all nearby/known Bluetooth devices with full config:

```
Device 0
  address:          AC:19:8E:D4:8A:95
  name:             boss
  bt_class:         8126732
  icon:             computer
  paired:           0
  bonded:           0
  connected:        0
  legacy pairing:   1
  uuid count:       16
  protocol:         BR/EDR

Device 4
  address:          41:42:48:74:47:6E
  name:             Noise Buds Marine
  paired:           1
  bonded:           1
  trusted:          1
  uuid count:       5
  protocol:         BR/EDR
```

---

## Key Concepts Learned

| Concept | Key Insight |
|---------|-------------|
| D-Bus | IPC message bus — query BlueZ like an API call |
| DBusError | Must be initialized — C doesn't zero variables automatically |
| DBusMessageIter | Cursor for walking nested typed data — recurse for containers |
| DBusBasicValue | Union for all primitive types — one variable, field selected by type |
| Recursive tree walker | Tree structure → recursive function; each level gets own stack frame |
| Local vs global state | Recursive calls don't share locals — use globals or pass as parameters |
| String comparison in C | `==` compares pointers, not content — always use `strcmp` |
| String copy in C | Cannot assign `char[]` directly — use `strncpy` |
| Protocol detection | Inferred from presence of `org.bluez.Bearer.BREDR1` interface at level 4 |
| Off-by-one | Increment count after filling, or use `count-1` when indexing |

---

## Files Produced

| File | Purpose |
|------|---------|
| `listener.c` | Script 1 — BT device enumerator |
| `bt_struct.h` | `BT_NODE` struct definition |

---

## Script 1 — Possible Future Iterations (Enhancement Only, Not Blocking)

These are enhancements to Script 1 that can be done later. Scripts 2, 3, 4 do **not** depend on them — they only need `address`, `connected`, and `protocol` from Script 1 which are already working.

| Iteration | Enhancement | What It Teaches |
|-----------|-------------|-----------------|
| 2 | Pairing method detection (Numeric Comparison / Passkey / Just Works / OOB) | SSP IO capability negotiation, LegacyPairing semantics |
| 3 | LESC detection (LE Secure Connections) | BT security model, key exchange, SDR track overlap |
| 4 | Class bitmask decoder — print human-readable device type | Bitwise operations, BT device class spec |
| 5 | UUID → profile name resolver — print "A2DP Sink" instead of UUID string | Lookup tables in C |

These will become meaningful when Script 4's anomaly detection needs security context to flag suspicious packets. Implement them then, not now.

---

## Session 07 — What's Next

### Immediate — Script 2 (Main Orchestrator)

Script 2 watches for BT connect/disconnect events in real time and allocates/deallocates threads for Scripts 3 and 4 accordingly.

What it needs from Script 1: `address` and `connected` — both already working.

Key concepts Script 2 will introduce:
- D-Bus signal watching (`PropertiesChanged` signal on `org.bluez.Device1`)
- `pthreads` — `pthread_create`, `pthread_join`, `pthread_cancel`
- Thread lifecycle management per device

### Pending — DSA Track (paused for BLE track, resume after BLE scripts complete)

These topics were queued from Session 05's progress report and remain pending. Will resume once Scripts 1–4 are complete.

| Topic | Detail | Source |
|-------|--------|--------|
| Hoare Partition | Two pointers from both ends; faster than Lomuto in practice | `algorithms_masterclass.md` §24 |
| 3-way Partition (Dutch Flag) | Partitions into `<`, `=`, `>`; O(n) when many duplicates | `algorithms_masterclass.md` §24 |
| Pivot Selection | Random pivot, median-of-three; avoiding O(n²) worst case | `algorithms_masterclass.md` §24 |
| Quick Sort Worst Case Analysis | When it degrades, why, adversarial inputs | `algorithms_masterclass.md` §24 |
