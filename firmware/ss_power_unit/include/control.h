#pragma once

#include "app_config.h"

void setupHardware();
void setupWiFiESPNow();
void controlRelay(bool state);
void setLEDState(LEDState newState);
float timeFromPosition(float x);
void savePosition(float x);
