# Block Diagram – Over & Under Voltage Protection System

```
                   ┌──────────────────────────────────────────────┐
                   │           AC MAINS (230V / 50Hz)             │
                   └─────────────────┬────────────────────────────┘
                                     │
                   ┌─────────────────▼────────────────────────────┐
                   │         Step-Down Transformer                 │
                   │         (230V AC → 9V AC)                     │
                   └─────────────────┬────────────────────────────┘
                                     │ 9V AC
                         ┌───────────┴───────────┐
                         │                       │
          ┌──────────────▼──────────┐   ┌────────▼──────────────────┐
          │  Voltage Sensor         │   │  5V DC Power Supply        │
          │  (ZMPT101B / divider)   │   │  (Bridge + 7805 / USB)     │
          │  → Analog signal        │   │  → Powers Arduino + LCD    │
          └──────────────┬──────────┘   └────────┬──────────────────┘
                         │ A0                     │ Vcc / GND
                         │              ┌─────────▼────────────────────┐
                         └─────────────►│         Arduino Uno           │
                                        │  - EmonLib (RMS calculation)  │
                                        │  - Hysteresis logic           │
                                        │  - D6 → LED                   │
                                        │  - D7 → Relay module          │
                                        │  - D8-D13 → 20×4 LCD         │
                                        └──┬──────────┬────────────────┘
                                           │          │
                          ┌────────────────▼──┐  ┌───▼────────────────────┐
                          │  20×4 LCD Display │  │  Relay Module (5V)      │
                          │  (Status + Vrms)  │  │  → Load (AC output)    │
                          └───────────────────┘  └────────────────────────┘
                                                          │
                                                 ┌────────▼───────────────┐
                                                 │    LED Indicator        │
                                                 │  ON  = load connected  │
                                                 │  OFF = fault / tripped │
                                                 └────────────────────────┘
```

## Signal Flow

| Stage | Component | Description |
|-------|-----------|-------------|
| 1 | Transformer | Steps 230V AC down to 9V AC for safe sensing |
| 2 | Voltage Sensor | Scales AC waveform to Arduino-safe analog range |
| 3 | Arduino Uno | Reads Vrms via EmonLib, applies threshold logic |
| 4 | LCD (20×4) | Displays live voltage and system status |
| 5 | Relay | Connects / disconnects load based on voltage level |
| 6 | LED | Visual indicator of relay / fault state |

## Voltage Thresholds

| Condition | Voltage Range | Action |
|-----------|---------------|--------|
| Normal | 197 V – 237 V | Relay ON, Load connected |
| Hysteresis band | 192–197 V or 237–242 V | Relay OFF, "Waiting to Reconnect" |
| Under Voltage | < 192 V | Relay OFF, LED ON |
| Over Voltage | > 242 V | Relay OFF, LED ON |
