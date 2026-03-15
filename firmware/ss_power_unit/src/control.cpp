#include "control.h"

#include <WiFi.h>
#include <esp_now.h>

#include "app_state.h"

void setupHardware() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(LOGIC_PIN, OUTPUT);
  digitalWrite(LOGIC_PIN, LOW);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  lastClkState = digitalRead(ENCODER_CLK);

  led.begin();
  led.setBrightness(255);
  led.show();
}

void setupWiFiESPNow() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    while (true) {
      delay(10);
    }
  }
}

void controlRelay(bool state) {
  digitalWrite(RELAY_PIN, state ? HIGH : LOW);
  Serial.print("Relay: ");
  Serial.println(state ? "ON" : "OFF");
}

void setLEDState(LEDState newState) {
  currentLEDState = newState;
}

float timeFromPosition(float x) {
  float result = 5.02779728e-08F;
  result = result * x - 2.86249445e-06F;
  result = result * x + 3.71093147e-05F;
  result = result * x + 8.20085287e-04F;
  result = result * x - 2.92747043e-02F;
  result = result * x + 3.28756698e-01F;
  result = result * x - 1.50065290e+00F;
  result = result * x + 2.92676443e+00F;
  result = result * x + 1.00000000e+00F;
  return result;
}

void savePosition(float x) {
  preferences.begin("encoder", false);
  preferences.putFloat("position", x);
  preferences.end();
}
