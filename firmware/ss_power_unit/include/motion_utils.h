#pragma once

#include "app_config.h"

float calculateMotionDelta(const MotionPacket &current, const MotionPacket &previous);
void updateMotionBuffer(float value);
float computeMovingAverage();
