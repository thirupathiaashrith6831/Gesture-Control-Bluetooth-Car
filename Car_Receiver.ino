#include <SoftwareSerial.h>

// SoftwareSerial setup: RX = Pin 2, TX = Pin 3
SoftwareSerial BT(2, 3); 

// L298N Pin Definitions
const int ENA = 9;  // Left Motor Speed (PWM)
const int IN1 = 4;  // Left Motor Direction
const int IN2 = 5;  // Left Motor Direction
const int IN3 = 6;  // Right Motor Direction
const int IN4 = 7;  // Right Motor Direction
const int ENB = 10; // Right Motor Speed (PWM)

// Default speed setting (0 to 255)
int carSpeed = 200; 

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopCar(); // Ensure motors start in an off state

  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Receiver Online. Listening for Bluetooth Commands...");
}

void loop() {
  if (BT.available()) {
    char command = BT.read();
    Serial.print("Executing Action: ");
    Serial.println(command);

    if (command == 'F') moveForward();
    else if (command == 'B') moveBackward();
    else if (command == 'L') turnLeft();
    else if (command == 'R') turnRight();
    else if (command == 'S') stopCar();
  }
}

void moveForward() {
  analogWrite(ENA, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, carSpeed);
}

void moveBackward() {
  analogWrite(ENA, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, carSpeed);
}

void turnLeft() {
  analogWrite(ENA, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); // Left side turns backward
  digitalWrite(IN3, HIGH); // Right side turns forward
  digitalWrite(IN4, LOW);
  analogWrite(ENB, carSpeed);
}

void turnRight() {
  analogWrite(ENA, carSpeed);
  digitalWrite(IN1, HIGH); // Left side turns forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Right side turns backward
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, carSpeed);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
