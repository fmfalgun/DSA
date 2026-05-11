# Bluetooth Device Info — How It Works

## The Chain: Hardware → OS → You

- **Hardware** — BT chip on your machine (here: `hci0`, BLE 5.0 capable)
- **Kernel** — loads HCI driver, exposes `/dev/hci0`
- **BlueZ** — userspace daemon (`bluetoothd`), sits on top of kernel, manages all BT state
- **D-Bus** — IPC bus BlueZ uses to expose its data to other programs
- **You** — query D-Bus to get everything BlueZ knows

---

## Why This Command

```bash
dbus-send --system --print-reply \
  --dest=org.bluez / \
  org.freedesktop.DBus.ObjectManager.GetManagedObjects
```

- `dbus-send` — CLI tool to send a D-Bus message
- `--system` — BlueZ lives on the **system bus** (not per-user session bus)
- `--dest=org.bluez` — address of the BlueZ process on the bus
- `/` — root object; only root exposes `ObjectManager`
- `GetManagedObjects` — returns **every** object BlueZ manages (adapters + devices)

---

## What It Depends On

| Factor | Detail |
|--------|--------|
| OS | Linux only — BlueZ is Linux-specific |
| BT Stack | Must be BlueZ (`bluetoothd` running) |
| D-Bus | System bus must be running (`dbus-daemon`) |
| Hardware | Any HCI-compatible BT adapter (`hci0`, `hci1`, ...) |
| Permissions | Must have access to system bus (root or `bluetooth` group) |

---

## Output Structure

```
array [
  /org/bluez              ← BlueZ root (skip)
  /org/bluez/hci0         ← your local adapter
  /org/bluez/hci0/dev_XX  ← external device (what you want)
  ...
]
```

Each object = path + interfaces + properties.

---

## How to Filter Device Details

**Step 1** — Walk all objects, keep only paths matching `/org/bluez/hciX/dev_*`

**Step 2** — Inside that object, find interface `org.bluez.Device1`

**Step 3** — Extract properties from that interface:

| Property | Type | Tells You |
|----------|------|-----------|
| `Address` | string | Device MAC (BDADDR) |
| `AddressType` | string | `public` / `random` |
| `Name` | string | Device display name |
| `Class` | uint32 | Device type bitmask (absent in BLE-only) |
| `Paired` | bool | Pairing done |
| `Bonded` | bool | LTK stored |
| `Trusted` | bool | Auto-connect allowed |
| `Blocked` | bool | Blacklisted |
| `Connected` | bool | Currently connected |
| `LegacyPairing` | bool | PIN-based (old) vs SSP/LESC |
| `ServicesResolved` | bool | GATT services discovered |
| `UUIDs` | array | Supported BT profiles |
| `RSSI` | int16 | Signal strength (only during active scan) |
| `Adapter` | path | Which `hciX` owns this device |

**Step 4** — Detect protocol from properties:

| Condition | Protocol |
|-----------|----------|
| `Class` present + `BREDR1` interface | Classic BR/EDR |
| `AddressType: random` or GATT UUIDs only | BLE |
| Both | Dual-mode |

