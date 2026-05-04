#### Kode Program
```cpp
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
```

---

### Penjelasan Setiap Baris Kode

```cpp
#include <Arduino_FreeRTOS.h>
```
Library untuk menggunakan sistem operasi real-time (FreeRTOS) pada Arduino agar dapat menjalankan beberapa task secara bersamaan.

```cpp
#include <Servo.h>
```
Library untuk mengontrol motor servo.

---

```cpp
#define LED_PIN 8
```
Menentukan pin digital 8 sebagai output untuk LED.

```cpp
#define SERVO_PIN 9
```
Menentukan pin digital 9 sebagai output untuk servo.

---

```cpp
Servo myServo;
```
Membuat objek servo dengan nama `myServo`.

```cpp
bool ledState = false;
```
Variabel untuk menyimpan kondisi LED (nyala atau mati).

---

```cpp
void TaskLED(void *pvParameters) {
```
Mendefinisikan task untuk mengontrol LED.

```cpp
pinMode(LED_PIN, OUTPUT);
```
Mengatur pin LED sebagai output.

```cpp
while (1) {
```
Loop tak hingga agar task berjalan terus-menerus.

```cpp
ledState = !ledState;
```
Membalik kondisi LED (ON menjadi OFF, OFF menjadi ON).

```cpp
digitalWrite(LED_PIN, ledState);
```
Menyalakan atau mematikan LED sesuai nilai `ledState`.

```cpp
vTaskDelay(1000 / portTICK_PERIOD_MS);
```
Memberikan delay selama 1000 ms (1 detik) menggunakan fungsi FreeRTOS.

```cpp
}
```
Menutup loop task LED.

```cpp
}
```
Menutup fungsi task LED.

---

```cpp
void TaskServo(void *pvParameters) {
```
Mendefinisikan task untuk mengontrol servo.

```cpp
myServo.attach(SERVO_PIN);
```
Menghubungkan servo ke pin yang telah ditentukan.

```cpp
while (1) {
```
Loop tak hingga untuk menjalankan task secara terus-menerus.

```cpp
if (ledState) {
```
Mengecek apakah LED dalam kondisi ON.

```cpp
myServo.write(90);
```
Jika LED ON, servo bergerak ke sudut 90 derajat.

```cpp
} else {
  myServo.write(0);
}
```
Jika LED OFF, servo kembali ke sudut 0 derajat.

```cpp
vTaskDelay(100 / portTICK_PERIOD_MS);
```
Memberikan delay 100 ms agar pergerakan servo stabil.

```cpp
}
```
Menutup loop task servo.

```cpp
}
```
Menutup fungsi task servo.

---

```cpp
void setup() {
```
Fungsi yang dijalankan sekali saat Arduino mulai.

```cpp
xTaskCreate(TaskLED, "LED Task", 128, NULL, 1, NULL);
```
Membuat task LED dengan ukuran stack 128 dan prioritas 1.

```cpp
xTaskCreate(TaskServo, "Servo Task", 128, NULL, 1, NULL);
```
Membuat task Servo dengan ukuran stack 128 dan prioritas 1.

```cpp
}
```
Menutup fungsi setup.

---

```cpp
void loop() {
}
```
Loop utama kosong karena semua proses sudah dijalankan oleh FreeRTOS melalui task.

---