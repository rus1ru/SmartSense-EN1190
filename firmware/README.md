# SmartSense Firmware

This directory contains firmware projects, experiments, and datasets used for SmartSense development.

## Architecture

The firmware is split into two ESP32 projects:

- `ss_motion_unit`: Motion sender node (currently scaffold-level implementation).
- `ss_power_unit`: Main receiver/controller node with production logic.

In `ss_power_unit`, the firmware uses:

- ESP-NOW receive callback to enqueue incoming `MotionPacket` data.
- FreeRTOS queue + mutex protection for concurrent task-safe processing.
- Moving-average motion filtering over a fixed-size ring buffer (`QUEUE_SIZE = 60`).
- State machine driven relay and LED behavior.
- Rotary encoder based timeout selection with NVS persistence (`Preferences`).

## Current Directory Layout

### `ss_motion_unit/`

PlatformIO project for the motion sensing unit.

- `platformio.ini`
- `src/main.cpp`
- `include/ulp_main.h`
- `include/esp32/ulp.h`
- `include/README`
- `lib/README`
- `test/README`

Status:

- `src/main.cpp` is currently the default PlatformIO template and should be replaced with sender logic for IMU sampling and packet transmission.

### `ss_power_unit/`

PlatformIO project for the power control unit.

- `platformio.ini`
- `src/main.cpp`
- `src/app_state.cpp`
- `src/control.cpp`
- `src/motion_utils.cpp`
- `src/tasks.cpp`
- `include/app_config.h`
- `include/app_state.h`
- `include/control.h`
- `include/motion_utils.h`
- `include/tasks.h`
- `include/README`
- `lib/README`
- `test/README`

Technical breakdown:

- `src/main.cpp`: Boot sequence, restores saved encoder position, initializes hardware/comms, starts RTOS tasks.
- `src/control.cpp`: GPIO setup, ESP-NOW init, relay control, LED mode updates, timeout mapping, NVS saves.
- `src/tasks.cpp`: Task creation and runtime logic (communication, motion processing, state machine, LED animation, encoder input).
- `src/motion_utils.cpp`: Motion delta and moving-average functions.
- `src/app_state.cpp`: Global shared state, queues/semaphores, LED mode table.

Core runtime states:

- `STATE_SEARCHING`
- `STATE_CONNECTED`
- `STATE_CONNECTED_IDLE`
- `STATE_POWER_OFF`
- `STATE_OVERRIDE`

Timeout behavior:

- Motion timeout and idle timeout are evaluated from packet timing and encoder-selected duration.
- The `timeFromPosition(...)` function maps encoder index to timeout minutes using a polynomial fit.

### `dataset/`

Data and analysis artifacts:

- `data_analysis.ipynb`
- `datasheet_csv.csv`
- `dataset_phase_1_with_is_high_accel.csv`
- `dataset_phase_2_with_is_high_accel.csv`
- `dataset_phase_3_with_is_high_accel.csv`
- `dataset_phase_4_with_is_high_accel.csv`
- `threshold_dataset.xlsx`
- `threshold_score_is_high_accel.png`
- `threshold_score_is_high_accel_2.png`
- `threshold_score_is_high_accel_3.png`

### `test_codes/`

Arduino and prototype test sketches:

- `nimble_test1_02_05.ino`
- `nimble_test/nimble_test.ino`
- `nimble_test2/nimble_test2.ino`
- `now_rec_test/now_rec_test.ino`
- `now_sleep_rec/now_sleep_rec.ino`
- `now_sleep_tra/now_sleep_tra.ino`
- `now_tra_test/now_tra_test.ino`
- `MPU6050_test/MPU6050_test.ino`
- `MPU6050_test/Processing/MPUTeapot/MPUTeapot.pde`
- `dev1_full/acclr_now_test_1/acclr_now_test_1.ino`
- `dev1_full/acclr_now_test_2_with_sleep/acclr_now_test_2_process_and _send.ino`
- `dev1_full/acclr_now_test_2_with_sleep/now_rec_test.ino`

## Build Notes

- The two production targets are managed as separate PlatformIO projects.
- Experimental sketches in `test_codes` are not part of the PlatformIO build by default.

## Build Commands

Run from this repository root:

```bash
cd firmware/ss_power_unit && pio run
cd firmware/ss_motion_unit && pio run
```

Flash examples:

```bash
cd firmware/ss_power_unit && pio run -t upload
cd firmware/ss_motion_unit && pio run -t upload
```

Copyright (c) 2025 AuraPlus.
All rights reserved.
