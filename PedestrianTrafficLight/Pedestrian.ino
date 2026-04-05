int redCar = 8;
int yellowCar = 7;
int greenCar = 6;

// Pedestrian (2 sisi)
int redPed1 = 5;
int greenPed1 = 4;

int redPed2 = 10;
int greenPed2 = 9;

// Tombol (Interrupt)
int btn1 = 2;
int btn2 = 3;

volatile bool buttonPressed = false;

void buttonISR() {
  buttonPressed = true;
}

void setup() {
  // Lampu kendaraan
  pinMode(redCar, OUTPUT);
  pinMode(yellowCar, OUTPUT);
  pinMode(greenCar, OUTPUT);

  // Lampu pedestrian
  pinMode(redPed1, OUTPUT);
  pinMode(greenPed1, OUTPUT);
  pinMode(redPed2, OUTPUT);
  pinMode(greenPed2, OUTPUT);

  // Tombol
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  // Attach interrupt (kedua tombol efek sama)
  attachInterrupt(digitalPinToInterrupt(btn1), buttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2), buttonISR, FALLING);

  // Kondisi awal
  digitalWrite(greenCar, HIGH);
  digitalWrite(yellowCar, LOW);
  digitalWrite(redCar, LOW);

  digitalWrite(redPed1, HIGH);
  digitalWrite(greenPed1, LOW);

  digitalWrite(redPed2, HIGH);
  digitalWrite(greenPed2, LOW);
}

void loop() {
  if (!buttonPressed) {
    // kendaraan hijau, pedestrian merah
    digitalWrite(greenCar, HIGH);
    digitalWrite(redCar, LOW);

    digitalWrite(redPed1, HIGH);
    digitalWrite(greenPed1, LOW);

    digitalWrite(redPed2, HIGH);
    digitalWrite(greenPed2, LOW);
  }
  else {
    digitalWrite(greenCar, LOW);
    digitalWrite(yellowCar, LOW);
    digitalWrite(redCar, HIGH);

    digitalWrite(redPed1, LOW);
    digitalWrite(greenPed1, HIGH);

    digitalWrite(redPed2, LOW);
    digitalWrite(greenPed2, HIGH);

    delay(5000); // waktu penyebrangan

    // 2. Pedestrian kembali MERAH
    digitalWrite(greenPed1, LOW);
    digitalWrite(redPed1, HIGH);

    digitalWrite(greenPed2, LOW);
    digitalWrite(redPed2, HIGH);

    // 3. Kendaraan KUNING (kedip 2 kali)
    digitalWrite(redCar, LOW);

    for (int i = 0; i < 3; i++) {
      digitalWrite(yellowCar, HIGH);
      delay(500);
      digitalWrite(yellowCar, LOW);
      delay(500);
    }

    // 4. Kembali ke kondisi awal (HIJAU)
    digitalWrite(greenCar, HIGH);

    // reset tombol
    buttonPressed = false;
  }
}