# Project Files

This directory contains the **Proteus 8** simulation project for the  
Over & Under Voltage Protection System.

## Contents

| File | Description |
|------|-------------|
| `Circuit.pdsprj` | Proteus 8 project file – open with Proteus Design Suite |

## How to Run the Simulation

1. Install **Proteus Design Suite 8.x** (or later).
2. Open `Circuit.pdsprj`.
3. Load the compiled firmware from `../src/voltage_protection.ino.hex`  
   into the virtual Arduino Uno component (right-click → Edit Properties → Program File).
4. Press **Run** (F9).
5. Adjust the AC voltage source value to test normal / over / under voltage scenarios.

## Dependencies

- [EmonLib](https://github.com/openenergymonitor/EmonLib) — included implicitly via compiled `.hex`
- Arduino LiquidCrystal library — standard Arduino library
