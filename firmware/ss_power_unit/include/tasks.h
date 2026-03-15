#pragma once

#include <esp_now.h>

void setupRTOS();

void communicationTask(void *pvParameters);
void motionProcessingTask(void *pvParameters);
void ledControlTask(void *pvParameters);
void encoderTask(void *pvParameters);
void stateMachineTask(void *pvParameters);

void onDataReceived(const esp_now_recv_info_t *info, const uint8_t *data, int len);
