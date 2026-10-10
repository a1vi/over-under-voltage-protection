# Test Evidence

This directory contains test screenshots and simulation captures taken during
the validation of the Over & Under Voltage Protection System.

## Test Results Summary

| Test ID | Condition | Input Voltage | Expected Result | Observed Result | Status |
|---------|-----------|---------------|-----------------|-----------------|--------|
| T-01 | Normal Operation | ~220 V AC | Relay ON, LCD "NORMAL VOLTAGE" | ✅ Relay ON, LCD correct | PASS |
| T-02 | Over-Voltage Fault | > 242 V AC | Relay OFF, LCD "OVER VOLTAGE" | ✅ Relay OFF, LED lit | PASS |
| T-03 | Under-Voltage Fault | < 192 V AC | Relay OFF, LCD "UNDER VOLTAGE" | ✅ Relay OFF, LED lit | PASS |
| T-04 | Hysteresis – reconnect | 197–237 V AC | Relay ON after recovery | ✅ Relay ON | PASS |
| T-05 | Hysteresis – hold off | 192–197 V or 237–242 V | Relay OFF, "WAITING…" | ✅ Relay held OFF | PASS |

## Screenshot Descriptions

| File | Condition Simulated |
|------|---------------------|
| `over_voltage.png` | Proteus simulation showing LCD reading above 242 V; relay de-energised |
| `safe.png` | Simulation showing LCD reading within 197–237 V; relay energised |
| `under_voltage.png` | Simulation showing LCD reading below 192 V; relay de-energised |

## Notes

- All tests performed in **Proteus 8** simulation using the compiled `.hex` firmware.
- Voltage sensor calibration constant: `187` (ratio factor), phase shift: `1.7`.
- EmonLib `calcVI(20, 500)` — 20 half-cycles, 500 ms timeout per reading.
