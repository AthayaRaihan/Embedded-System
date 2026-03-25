// C++ code
//

// struct initiate
struct traffic { 
  int red;
  int yellow;
  int green;
};

// insert lamp code
traffic roads[4] = { 
  {13, 12, 11},
  {10, 9, 8},
  {7, 6, 5},
  {4, 3, 2}
};

void setup()
{
  // North
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  
  // East
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);

  // South
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  // West
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  
  // All Red (Initial State)
  for (int i = 0; i < 4; i++) {
    digitalWrite(roads[i].red, HIGH);
    digitalWrite(roads[i].yellow, LOW);
    digitalWrite(roads[i].green, LOW);
  }
  delay(3000);
  
  // turn yellow  
  digitalWrite(13, LOW);
  for (int i = 0; i < 3; i++) { // yellow light blink loop
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);
    delay(500);
  };
  digitalWrite(12, HIGH); // yellow 2secs light
  delay(2000);
  
  digitalWrite(12, LOW); // off yellow
  digitalWrite(11, HIGH); // on green 
  delay(5000);
}

// lamp color turnover function
void activeRoad (struct traffic R1, struct traffic R2) {
  // turn off current lamp
  digitalWrite(R1.green, LOW);
  digitalWrite(R2.red, LOW);
  
  // yellow blink loop
  for (int i = 0; i < 3; i++) {
  	digitalWrite(R1.yellow, HIGH);
   	digitalWrite(R2.yellow, HIGH);
    delay(500);
    digitalWrite(R1.yellow, LOW);
   	digitalWrite(R2.yellow, LOW);
    delay(500);
  }
  
  digitalWrite(R1.yellow, HIGH);
  digitalWrite(R2.yellow, HIGH);
  delay(2000); // 2secs yellow light
  digitalWrite(R1.yellow, LOW);
  digitalWrite(R2.yellow, LOW);
  
  // turn on next lamp
  digitalWrite(R1.red, HIGH);
  digitalWrite(R2.green, HIGH);
  delay(5000);
}

void loop()
{    
  // === North Road ===
  activeRoad(roads[0], roads[1]);
  
  // === East Road ===
  activeRoad(roads[1], roads[2]);
  
  // === South Road ===
  activeRoad(roads[2], roads[3]);
  
  // === West Road ===
  activeRoad(roads[3], roads[0]);
}