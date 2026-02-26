# SmartSense Firmware 💻

This directory contains the embedded software required to run the SmartSense motion-sensing auto-cutoff system. The firmware processes raw MPU6050 data to detect inertia/movement, runs the inactivity timer logic, and triggers the power cutoff sequence.

---

## 🔄 How it Works

1. **Initialization:** The microcontroller initializes the I2C bus and verifies communication with the MPU6050.
2. **Calibration:** On startup, the MPU6050 takes base readings to calibrate the gyroscope and accelerometer offsets. Ensure the device is flat and still during power-up!
3. **Loop Logic:**
   - Continuously reads acceleration ($ax, ay, az$) and gyroscope ($gx, gy, gz$) values.
   - Calculates the magnitude of acceleration to determine if the iron is currently moving.
   - If acceleration stays below a defined `MOTION_THRESHOLD` for `TIMEOUT_DURATION`, the system flags an "Idle" state.
4. **Trigger:** Once the Idle state duration exceeds the safety limit, the microcontroller asserts a GPIO pin to HIGH/LOW to trigger the relay, cutting the power. An optional buzzer sequence plays just before cutoff.

---

## ⚙️ Setup & Flashing Instructions

### Requirements

- A suitable IDE (e.g., **Arduino IDE**, **PlatformIO** via VSCode).
- Appropriate board manager installed for your microcontroller (ESP32 / Arduino AVR).
- USB-C/Micro-USB cable for flashing.

### Required Libraries

Depending on the specific `main` file, you might need:

- `Wire.h` (Built-in I2C library)
- `Adafruit_MPU6050` or standard `MPU6050` by Electronic Cats.
- `Adafruit_Sensor`

_(You can install these via the Arduino Library Manager or define them in your `platformio.ini`)_

### Flashing

1. Connect the microcontroller to your PC.
2. Open the main `.ino` or `.cpp` file in your IDE.
3. Select the correct Board and COM Port.
4. Hit **Upload**.

---

## 🎛️ Configuration Variables

You can adjust the sensitivity and timeout duration at the top of the main code file:

```cpp
#define TIMEOUT_DURATION 300000  // In milliseconds (default to 5 minutes)
#define MOTION_THRESHOLD 1.5     // Sensitivity threshold for motion vs idle
#define RELAY_PIN 4              // GPIO pin connected to the relay
#define BUZZER_PIN 5             // GPIO pin connected to the buzzer (optional)
```

---

© 2025 AuraPlus. All rights reserved.
