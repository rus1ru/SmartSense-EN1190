# SmartSense

MPU6050-based motion sensing iron auto shut-off system.

This repository includes the mechanical enclosure design, PCB design, firmware, and project deliverables (presentation and reports).

## Technical Overview

SmartSense is organized as a two-unit ESP32 architecture:

1. Motion unit: Captures IMU readings and transmits motion packets wirelessly.
2. Power unit: Receives packets, computes activity/idle state, and controls the relay.

Current power-unit firmware uses:

- `ESP-NOW` in station mode for low-latency packet reception.
- `FreeRTOS` tasks pinned to ESP32 cores for communication, motion processing, state management, LED signaling, and encoder handling.
- Moving-average filtering on acceleration delta magnitude to suppress noise before thresholding.

Relay behavior is state-driven and includes manual override via encoder button hold.

## Repository Layout

```text
SmartSense-EN1190/
├── cad_files/
│   ├── Assemblies/
│   ├── Drawings/
│   ├── Manufacturing/
│   ├── Parts/
│   ├── PCB Step Files/
│   ├── Sketches/
│   ├── Vizualize/
│   └── README.md
├── firmware/
│   ├── dataset/
│   ├── ss_motion_unit/
│   ├── ss_power_unit/
│   ├── test_codes/
│   └── README.md
├── pcb_files/
│   ├── PCBs/
│   ├── Schematics/
│   └── README.md
├── presentations/
│   ├── AuraPlus_FInal Presentation.pptx
│   └── README.md
├── reports/
│   ├── AuraPlus_FInal Report.pdf
│   ├── Manual.pdf
│   ├── Mkt_Flyer.jpeg
│   └── README.md
└── README.md
```

## System Summary

1. Motion is detected using the MPU6050.
2. Firmware computes motion delta from acceleration vectors and smooths it via a fixed window average.
3. Inactivity timeout is selected with a rotary encoder and persisted in non-volatile storage.
4. On timeout, the power unit transitions to a power-off state and de-energizes the relay.

## Firmware Runtime Model

- Default state: `STATE_SEARCHING` until valid wireless packets are received.
- Connected motion state: Relay ON while packets are present and motion is active.
- Connected idle state: Countdown runs based on encoder-selected timeout.
- Power-off state: Relay OFF when idle timeout is exceeded.
- Override state: Manual forced ON state, toggled by long-press action.

The power unit includes LED state mapping for each system mode (searching, connected, idle, power off, override) to provide local user feedback.

## Main Work Areas

- `cad_files`: Mechanical parts, assemblies, manufacturing STL files, and visual assets.
- `firmware`: PlatformIO projects for motion and power units, datasets, and test sketches.
- `pcb_files`: Altium PCB and schematic source files.
- `presentations`: Final project presentation deck.
- `reports`: Final report, manual, and marketing flyer.

## Build and Toolchain

- MCU platform: ESP32 DevKit (`esp32doit-devkit-v1`).
- Build system: PlatformIO (`framework = arduino`).
- ECAD source: Altium (`.PcbDoc`, `.SchDoc`).
- MCAD source: SolidWorks (`.SLDPRT`, `.SLDASM`), with STL/STEP exports for manufacturing and integration.

## License

Copyright (c) 2025 AuraPlus.
All rights reserved.
