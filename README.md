# SmartSense 🔥📦

**MPU6050-Based Motion Sensing Iron Auto Shut-off System**

IronGuard-MPU is a safety and automation project aimed at reducing fire hazards and saving electricity. It uses the **MPU6050 6-axis motion sensor** to track iron movement. If no motion is detected for a preset duration, the system automatically shuts off power via a relay.

---

## 🚀 Features

- 🧠 **MPU6050 Motion Detection**
- ⏱️ **Inactivity Timer**
- 🔌 **Relay-Based Power Cut-off**
- 🔋 **Low-Power Microcontroller Compatible (ATmega328/ESP32)**
- 🔔 **Optional Buzzer Alert Before Shut-off**
- 🧱 **Compact Design, Can Be Plug-Integrated**

---

## 🧱 Components

- **MPU6050 Accelerometer + Gyroscope**
- **Microcontroller (e.g., ESP32, Arduino Nano, ATtiny85)**
- **Relay Module (5V or 3.3V logic compatible)**
- **Buzzer (Optional)**
- **Power Supply (USB or 5V DC Adapter)**

---

## 🔧 How It Works

1. The **MPU6050** tracks acceleration and angular velocity.
2. If the iron is idle (below a movement threshold) for **X minutes**, a timer starts.
3. After the timeout, the **relay module** disconnects power to the iron.
4. An optional **buzzer** or **LED** gives the user a warning before shutoff.

---

## 📦 Folder Structure

SmartSense/
├── firmware/
│ └── main.ino
├── schematics/
│ └── iron_auto_cutoff_circuit.pdf
├── 3d-print/
│ └── case_model.stl
├── README.md
└── LICENSE


---

## 📲 Optional Add-ons

- BLE notification via ESP32
- Mobile App for status/override
- OTA firmware update

---

## 🛡️ License

© 2025 AuraPlus. All rights reserved.

This project and all associated files are proprietary and confidential. 
Redistribution, reproduction, or use of any part of this system without 
explicit written permission is strictly prohibited.

Patent pending.

---

## 👨‍💻 Author

**SmartSense**  
Created by AuraPlus, University of Moratuwa  
Electronics & Telecommunication Engineering
