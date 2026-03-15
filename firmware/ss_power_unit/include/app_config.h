#pragma once

#include <Arduino.h>

// ---------------- CONFIG ----------------
constexpr int RELAY_PIN = 21;          // Relay module pin
constexpr int ENCODER_CLK = 6;         // Encoder Channel A
constexpr int ENCODER_DT = 5;          // Encoder Channel B
constexpr int ENCODER_SW = 7;          // Encoder push button
constexpr int LED_PIN = 4;             // RGB LED data pin
constexpr int LOGIC_PIN = 2;           // Logic pin for relay control
constexpr int NUM_PIXELS = 1;          // Single RGB LED
constexpr float MOTION_THRESHOLD = 0.1F;
constexpr int QUEUE_SIZE = 60;         // Moving average window
constexpr uint32_t SEARCH_TIMEOUT = 10000;      // 10 seconds
constexpr uint32_t OVERRIDE_HOLD_TIME = 5000;   // 5 seconds

// ----------- SYSTEM STATES -----------
enum SystemState {
  STATE_SEARCHING,
  STATE_CONNECTED,
  STATE_CONNECTED_IDLE,
  STATE_POWER_OFF,
  STATE_OVERRIDE
};

// ----------- LED STATE DEFINITIONS -----------
enum LEDState {
  LED_OFF = 0,
  LED_SOLID_RED,
  LED_SOLID_GREEN,
  LED_SOLID_BLUE,
  LED_BLINK_YELLOW,
  LED_FADE_LAVENDER,
  LED_SOLID_WHITE,
  LED_BLINK_ORANGE
};

// ----------- State config -----------
struct LEDMode {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  bool blink;
  bool fade;
  uint16_t interval;
};

// ----------- Motion packet -----------
struct MotionPacket {
  uint32_t packetId;
  float accX;
  float accY;
  float accZ;
  float gyroX;
  float gyroY;
  float gyroZ;
  float temperature;
};
