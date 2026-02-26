# SmartSense CAD & Hardware Design 🛠️

This directory contains the mechanical design files, 3D printing ready models, and assembly instructions for the SmartSense hardware casing. The enclosure is designed to be compact, heat-resistant, and easily integrable into existing power line systems or plugs.

---

## 📂 Directory Contents

- **`solidworks/`**: Native SolidWorks (`.SLDPRT`, `.SLDASM`) files containing the raw design. Use these if you need to modify the dimensions, adjust mount points, or remix the design.
- **`stl/`**: Exported 3D printable `.stl` files. These are ready to be sliced and printed.
- **`renders/`**: High-quality render images of the final assembled enclosure.

---

## 🖨️ 3D Printing Guidelines

For the best durability and safety (since the device is used near high-temperature equipment like an iron), we highly recommend the following print settings:

- **Material:** PETG or ABS (Avoid PLA as it may warp under heat).
- **Layer Height:** 0.2mm for a good balance of speed and structural integrity.
- **Infill:** 20-30% Grid or Gyroid.
- **Supports:** Required only for overhanging mounting tabs.
- **Wall Thickness:** Minimum 3 perimeters for strength.

---

## 🔧 Assembly Instructions

1. **Base Plate Preparation:** Insert the threaded brass inserts (M3) into the base plate using a soldering iron.
2. **PCB Mounting:** Mount the SmartSense PCB onto the base standoffs. Secure it using M3 nuts.
3. **Sensor Placement:** Ensure the MPU6050 is housed correctly in its dedicated slot without any mechanical stress to ensure accurate readings.
4. **Relay Wiring:** Route the high-voltage relay cables through the designated strain-relief channels. Ensure all connections are isolated to prevent short circuits.
5. **Top Cover:** Snap the top cover into place and secure it from the bottom using M3 screws.

---

> [!WARNING]
> **Safety First!** The enclosure houses high-voltage components. Ensure that the casing is completely sealed and printed with fire-retardant or high-heat resistant material to avoid accidental shocks or melting.

---

© 2025 AuraPlus. All rights reserved.
