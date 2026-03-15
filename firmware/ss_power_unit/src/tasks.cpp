#include "tasks.h"

#include <esp_now.h>

#include "app_config.h"
#include "app_state.h"
#include "control.h"
#include "motion_utils.h"

void setupRTOS() {
  stateMutex = xSemaphoreCreateMutex();
  dataMutex = xSemaphoreCreateMutex();

  motionQueue = xQueueCreate(10, sizeof(MotionPacket));

  xTaskCreatePinnedToCore(
      communicationTask,
      "Comm Task",
      4096,
      nullptr,
      4,
      &commTaskHandle,
      0);

  xTaskCreatePinnedToCore(
      motionProcessingTask,
      "Motion Task",
      4096,
      nullptr,
      3,
      &motionTaskHandle,
      0);

  xTaskCreatePinnedToCore(
      stateMachineTask,
      "State Task",
      4096,
      nullptr,
      2,
      &stateTaskHandle,
      0);

  xTaskCreatePinnedToCore(
      ledControlTask,
      "LED Task",
      2048,
      nullptr,
      1,
      &ledTaskHandle,
      1);

  xTaskCreatePinnedToCore(
      encoderTask,
      "Encoder Task",
      2048,
      nullptr,
      1,
      &encoderTaskHandle,
      1);
}

void onDataReceived(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  (void)info;
  if (len == static_cast<int>(sizeof(MotionPacket))) {
    MotionPacket packet;
    memcpy(&packet, data, sizeof(packet));

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(motionQueue, &packet, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken) {
      portYIELD_FROM_ISR();
    }
  }
}

void communicationTask(void *pvParameters) {
  (void)pvParameters;
  esp_now_register_recv_cb(onDataReceived);

  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void motionProcessingTask(void *pvParameters) {
  (void)pvParameters;
  MotionPacket packet;
  Serial.println("Motion Processing Task Started");

  for (;;) {
    if (xQueueReceive(motionQueue, &packet, pdMS_TO_TICKS(100))) {
      Serial.println("Motion data received");

      xSemaphoreTake(stateMutex, portMAX_DELAY);
      lastPacketTime = millis();
      xSemaphoreGive(stateMutex);

      const float motion = calculateMotionDelta(packet, lastData);
      lastData = packet;

      updateMotionBuffer(motion);

      const float avgMotion = computeMovingAverage();
      Serial.print("Avg Motion: ");
      Serial.println(avgMotion);

      if (avgMotion > MOTION_THRESHOLD) {
        xSemaphoreTake(stateMutex, portMAX_DELAY);
        lastMotionTime = millis();
        xSemaphoreGive(stateMutex);
      }
    }

    vTaskDelay(1);
  }
}

void stateMachineTask(void *pvParameters) {
  (void)pvParameters;
  const TickType_t stateCheckInterval = pdMS_TO_TICKS(500);

  for (;;) {
    const unsigned long now = millis();
    const bool timeout = (now - lastPacketTime) > SEARCH_TIMEOUT;
    const bool motionTimeout = (now - lastMotionTime) > 1000;
    const bool idleTimeout = (now - lastMotionTime) > (timeFromPosition(encoderPosition) * 60000);
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    switch (currentSystemState) {
      case STATE_SEARCHING:
        if (lastPacketTime > 0 && !timeout) {
          currentSystemState = STATE_CONNECTED;
          Serial.println("Changed state to Connected");
          controlRelay(true);
        } else if (overrideEngaged) {
          currentSystemState = STATE_OVERRIDE;
          Serial.println("Changed state to Override");
          controlRelay(true);
        }
        break;

      case STATE_CONNECTED:
        if (motionTimeout) {
          currentSystemState = STATE_CONNECTED_IDLE;
          Serial.println("Changed state to Connected Idle");
        } else if (overrideEngaged) {
          currentSystemState = STATE_OVERRIDE;
          Serial.println("Changed state to Override");
        } else if (timeout) {
          currentSystemState = STATE_SEARCHING;
          Serial.println("Changed state to Searching");
          controlRelay(false);
        }
        break;

      case STATE_CONNECTED_IDLE:
        if (!motionTimeout) {
          currentSystemState = STATE_CONNECTED;
          Serial.println("Changed state to Connected");
        } else if (idleTimeout) {
          currentSystemState = STATE_POWER_OFF;
          Serial.println("Changed state to Power Off");
          controlRelay(false);
        } else if (overrideEngaged) {
          currentSystemState = STATE_OVERRIDE;
          Serial.println("Changed state to Override");
          controlRelay(true);
        } else if (timeout) {
          currentSystemState = STATE_SEARCHING;
          Serial.println("Changed state to Searching");
          controlRelay(false);
        }
        break;

      case STATE_POWER_OFF:
        if (lastPacketTime > 0 && !timeout) {
          if (!motionTimeout) {
            currentSystemState = STATE_CONNECTED;
            Serial.println("Changed state to Connected");
            controlRelay(true);
          } else if (overrideEngaged) {
            currentSystemState = STATE_OVERRIDE;
            Serial.println("Changed state to Override");
            controlRelay(true);
          }
        } else if (timeout) {
          currentSystemState = STATE_SEARCHING;
          Serial.println("Changed state to Searching");
          controlRelay(false);
        }
        break;

      case STATE_OVERRIDE:
        if (!overrideEngaged) {
          if (lastPacketTime > 0) {
            currentSystemState = STATE_CONNECTED;
            Serial.println("Changed state to Connected");
          } else {
            currentSystemState = STATE_SEARCHING;
            Serial.println("Changed state to Searching");
            controlRelay(false);
          }
        }
        break;
    }

    switch (currentSystemState) {
      case STATE_SEARCHING:
        setLEDState(LED_BLINK_ORANGE);
        break;
      case STATE_CONNECTED:
        setLEDState(LED_SOLID_GREEN);
        break;
      case STATE_CONNECTED_IDLE:
        setLEDState(LED_SOLID_BLUE);
        break;
      case STATE_POWER_OFF:
        setLEDState(LED_SOLID_WHITE);
        break;
      case STATE_OVERRIDE:
        setLEDState(LED_SOLID_RED);
        break;
      default:
        setLEDState(LED_OFF);
        break;
    }

    xSemaphoreGive(stateMutex);
    vTaskDelay(stateCheckInterval);
  }
}

void ledControlTask(void *pvParameters) {
  (void)pvParameters;
  unsigned long lastUpdate = 0;
  bool isOn = false;
  uint8_t fadeBrightness = 0;
  int fadeDir = 5;

  for (;;) {
    const LEDMode &mode = LED_STATES[currentLEDState];
    const unsigned long now = millis();

    if (mode.blink) {
      if (now - lastUpdate >= mode.interval) {
        lastUpdate = now;
        isOn = !isOn;
        led.setPixelColor(0, isOn ? led.Color(mode.r, mode.g, mode.b) : 0);
        led.show();
      }
    } else if (mode.fade) {
      if (now - lastUpdate >= mode.interval) {
        lastUpdate = now;
        fadeBrightness = static_cast<uint8_t>(fadeBrightness + fadeDir);
        if (fadeBrightness <= 0 || fadeBrightness >= 255) {
          fadeDir *= -1;
        }
        led.setBrightness(fadeBrightness);
        led.setPixelColor(0, led.Color(mode.r, mode.g, mode.b));
        led.show();
      }
    } else {
      led.setBrightness(255);
      led.setPixelColor(0, led.Color(mode.r, mode.g, mode.b));
      led.show();
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void encoderTask(void *pvParameters) {
  (void)pvParameters;
  unsigned long buttonPressStart = 0;
  bool buttonActive = false;

  int stepCounter = 0;
  int aState;
  int aLastState = digitalRead(ENCODER_CLK);

  for (;;) {
    aState = digitalRead(ENCODER_CLK);

    if (aState != aLastState) {
      if (digitalRead(ENCODER_DT) != aState) {
        stepCounter++;
      } else {
        stepCounter--;
      }

      if (stepCounter >= 1) {
        encoderPosition = (encoderPosition + 1) % 24;
        stepCounter = 0;
        savePosition(encoderPosition);
        Serial.print("Current Position: ");
        Serial.println(encoderPosition);
        Serial.print("Current Timeout: ");
        Serial.println(timeFromPosition(encoderPosition));
      } else if (stepCounter <= -1) {
        encoderPosition = (encoderPosition + 23) % 24;
        stepCounter = 0;
        savePosition(encoderPosition);
        Serial.print("Current Position: ");
        Serial.println(encoderPosition);
        Serial.print("Current Timeout: ");
        Serial.println(timeFromPosition(encoderPosition));
      }
    }

    aLastState = aState;

    if (digitalRead(ENCODER_SW) == LOW) {
      if (!buttonActive) {
        buttonActive = true;
        buttonPressStart = millis();
      } else if (millis() - buttonPressStart > OVERRIDE_HOLD_TIME) {
        xSemaphoreTake(stateMutex, portMAX_DELAY);
        overrideEngaged = !overrideEngaged;
        Serial.print("Override ");
        Serial.println(overrideEngaged ? "ENGAGED" : "DISENGAGED");
        xSemaphoreGive(stateMutex);
        buttonActive = false;
      }
    } else {
      buttonActive = false;
    }

    vTaskDelay(pdMS_TO_TICKS(1));
  }
}
