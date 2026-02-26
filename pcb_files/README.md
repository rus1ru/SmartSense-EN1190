# SmartSense PCB Design & Manufacturing ⚡

This directory contains the electrical schematics, PCB board layouts, and manufacturing files required to produce the SmartSense hardware platform. The PCB is designed to compactly fit the MPU6050, the microcontroller, and power circuitry.

---

## 📂 Directory Contents

- **`schematics/`**: Contains the PDF and raw project files (such as Altium, KiCad, or Eagle) for the circuit schematics.
- **`board/`**: Contains the native PCB layout files. Use these to view or modify traces and component placements.
- **`gerbers/`**: Contains the generated Gerber files (`.gbr`, drill files) needed for PCB manufacturing (e.g., JLCPCB, PCBWay).
- **`bom/`**: The Bill of Materials (BOM) in CSV/Excel format detailing all components, values, footprints, and potential supplier links.

---

## 🧩 Key Components Overview

- **Sensors:** MPU6050 (6-axis accelerometer & gyroscope)
- **Microcontroller:** ESP32 / Arduino Nano / ATtiny85 (Refer to BOM for the exact model used in the current iteration)
- **Power Delivery:** 5V DC regulation circuitry. High-side or Low-side relay driver mechanism.
- **Actuators:** 5V/3.3V Logic Level Relay for cutting high-power AC loads, Optional Buzzer logic.

---

## 🏭 Manufacturing Instructions

To fabricate this PCB:

1. Download the `.zip` file from the `/gerbers` directory.
2. Upload it to your preferred PCB manufacturer.
3. **Recommended Specs:**
   - **Thickness:** 1.6mm
   - **Copper Weight:** 1 oz (or 2 oz if high current traces need extra handling)
   - **Layers:** 2-Layer Board
   - **Silkscreen/Solder Mask:** Any color of preference.

---

> [!CAUTION]
> **High Voltage Hazard!** The relay module interacts with mains electricity. Ensure proper trace width for the mains voltage lines and maintain adequate creepage/clearance isolation distances between the high-voltage and low-voltage sections on the PCB.

---

© 2025 AuraPlus. All rights reserved.
