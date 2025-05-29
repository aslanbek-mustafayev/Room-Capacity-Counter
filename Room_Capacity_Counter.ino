// Room Capacity Counter with Arduino Uno
// Tracks number of people entering and exiting a room using two HC-SR04 sensors
// Displays count on a Nokia 5110 LCD and manages entry restriction with LEDs

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Ultrasonic sensor pins
#define trigPin1 6
#define echoPin1 7
#define trigPin2 8
#define echoPin2 9

// LED pins
int led1 = 10; // Green LED (entry)
int led2 = 11; // Red LED (entry)
int led3 = 12; // Red LED (exit)
int led4 = 13; // Green LED (exit)

// LCD object
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3, 2, 1);

// Variables for sensor timing and distance
unsigned long duration1 = 0;
unsigned long duration2 = 0;
int distance1;
int distance2;
int visitor = 0; // Number of people in the room

void setup() {
  display.begin();
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void measureDistance1() {
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
}

void measureDistance2() {
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
}

int calculateDistance1() {
  measureDistance1();
  return int((duration1 / 2) / 29); // Sound speed: 29 us/cm
}

int calculateDistance2() {
  measureDistance2();
  return int((duration2 / 2) / 29);
}

void loop() {
  display.setTextSize(1);
  display.setTextColor(BLACK);

  digitalWrite(led1, HIGH); // Entry green LED ON
  digitalWrite(led4, HIGH); // Exit green LED ON

  if (visitor == 5) {
    digitalWrite(led1, LOW); // Entry green LED OFF
    digitalWrite(led2, HIGH); // Entry red LED ON
    digitalWrite(led3, LOW); // Exit red LED OFF
    digitalWrite(led4, HIGH); // Exit green LED ON

    display.clearDisplay();
    display.setTextSize(2);
    display.println(" --/->");
    display.setTextSize(1);
    display.println(" MAX 5 PERSON");
    display.setTextSize(2);
    display.print(" <----");
  } else {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }

  distance1 = calculateDistance1();
  distance2 = calculateDistance2();

  if (distance1 < 10) {
    delay(1000);
    distance2 = calculateDistance2();
    if (distance2 < 10 && visitor < 5) {
      visitor++;
      display.clearDisplay();
      display.setTextSize(1);
      display.println(" There is/are ");
      display.setTextSize(2);
      display.println(visitor);
      display.setTextSize(1);
      display.println(" person in the room");
      digitalWrite(led1, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
  } else if (distance2 < 10) {
    delay(1000);
    distance1 = calculateDistance1();
    if (distance1 < 10 && visitor > 0) {
      visitor--;
      display.clearDisplay();
      display.setTextSize(1);
      display.println(" There is/are ");
      display.setTextSize(2);
      display.println(visitor);
      display.setTextSize(1);
      display.println(" person in the room");
      digitalWrite(led1, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
  }

  display.display();
  delay(500);
}