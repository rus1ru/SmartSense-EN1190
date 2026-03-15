#include <Arduino.h>

#include "app_state.h"
#include "control.h"
#include "tasks.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Receiver Started");

  preferences.begin("encoder", true);
  const float savedPosition = preferences.getFloat("position", 0.0F);
  preferences.end();
  encoderPosition = static_cast<int>(savedPosition);

  setupHardware();
  setupWiFiESPNow();
  setupRTOS();
}

void loop() {
  // All logic is handled by FreeRTOS tasks.
  vTaskDelete(nullptr);
}