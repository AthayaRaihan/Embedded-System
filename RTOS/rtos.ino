#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#define LED_PIN 8
#define SERVO_PIN 9

Servo myServo;
bool ledState = false;

// Task 1: LED
void TaskLED(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);

  while (1) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task 2: Servo
void TaskServo(void *pvParameters) {
  myServo.attach(SERVO_PIN);

  while (1) {
    if (ledState) {
      myServo.write(90);  // LED ON
    } else {
      myServo.write(0);   // LED OFF
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  xTaskCreate(TaskLED, "LED Task", 128, NULL, 1, NULL);
  xTaskCreate(TaskServo, "Servo Task", 128, NULL, 1, NULL);
}

void loop() {
}