#include "app_state.h"

TaskHandle_t commTaskHandle = nullptr;
TaskHandle_t motionTaskHandle = nullptr;
TaskHandle_t ledTaskHandle = nullptr;
TaskHandle_t encoderTaskHandle = nullptr;
TaskHandle_t stateTaskHandle = nullptr;

QueueHandle_t motionQueue = nullptr;
SemaphoreHandle_t stateMutex = nullptr;
SemaphoreHandle_t dataMutex = nullptr;

volatile SystemState currentSystemState = STATE_SEARCHING;
volatile LEDState currentLEDState = LED_BLINK_ORANGE;
unsigned long lastPacketTime = 0;
unsigned long lastMotionTime = 0;
bool overrideEngaged = false;

MotionPacket currentData = {0};
MotionPacket lastData = {0};

float motionValues[QUEUE_SIZE] = {0.0F};
int motionIndex = 0;
bool motionBufferFull = false;

volatile int encoderPosition = 0;
int lastClkState = 0;

Adafruit_NeoPixel led(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Preferences preferences;

const LEDMode LED_STATES[] = {
    {0, 0, 0, false, false, 0},
    {255, 0, 0, false, false, 0},
    {0, 255, 0, false, false, 0},
    {0, 0, 255, false, false, 0},
    {255, 255, 0, true, false, 500},
    {230, 230, 250, false, true, 20},
    {255, 255, 255, false, false, 0},
    {255, 165, 0, true, false, 500},
};
