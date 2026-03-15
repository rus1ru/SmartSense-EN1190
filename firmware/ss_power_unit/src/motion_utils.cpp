#include "motion_utils.h"

#include <math.h>

#include "app_state.h"

float calculateMotionDelta(const MotionPacket &current, const MotionPacket &previous) {
  const float dx = current.accX - previous.accX;
  const float dy = current.accY - previous.accY;
  const float dz = current.accZ - previous.accZ;
  return sqrtf(dx * dx + dy * dy + dz * dz);
}

void updateMotionBuffer(float value) {
  xSemaphoreTake(dataMutex, portMAX_DELAY);
  motionValues[motionIndex] = value;
  motionIndex = (motionIndex + 1) % QUEUE_SIZE;
  if (motionIndex == 0) {
    motionBufferFull = true;
  }
  xSemaphoreGive(dataMutex);
}

float computeMovingAverage() {
  xSemaphoreTake(dataMutex, portMAX_DELAY);
  const int count = motionBufferFull ? QUEUE_SIZE : motionIndex;
  float sum = 0.0F;
  for (int i = 0; i < count; i++) {
    sum += motionValues[i];
  }
  xSemaphoreGive(dataMutex);
  return count > 0 ? (sum / static_cast<float>(count)) : 0.0F;
}
