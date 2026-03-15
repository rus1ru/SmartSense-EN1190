#pragma once

#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include "app_config.h"

extern TaskHandle_t commTaskHandle;
extern TaskHandle_t motionTaskHandle;
extern TaskHandle_t ledTaskHandle;
extern TaskHandle_t encoderTaskHandle;
extern TaskHandle_t stateTaskHandle;

extern QueueHandle_t motionQueue;
extern SemaphoreHandle_t stateMutex;
extern SemaphoreHandle_t dataMutex;

extern volatile SystemState currentSystemState;
extern volatile LEDState currentLEDState;
extern unsigned long lastPacketTime;
extern unsigned long lastMotionTime;
extern bool overrideEngaged;

extern MotionPacket currentData;
extern MotionPacket lastData;

extern float motionValues[QUEUE_SIZE];
extern int motionIndex;
extern bool motionBufferFull;

extern volatile int encoderPosition;
extern int lastClkState;

extern Adafruit_NeoPixel led;
extern Preferences preferences;

extern const LEDMode LED_STATES[];
