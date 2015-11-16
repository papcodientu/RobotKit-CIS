/* RobotKit
 * Using Arduino board to control 2-wheel robot using motor drive TB6612
 * 
 * Copyright 2015 by PAP Mechatronic Technology
 * Release 1.0
 * Date 16-Nov-2015
 */
#define TARGET_SPEED 80
#define TURN_LEFT_DELAY 200
#define BACKWARD_DELAY 300

//#define ULTRASONIC

#define MAX_DISTANCE 15
// ultrasonic sensor
const int echoPin = 4;
const int trigPin = 5;
unsigned long distance = 0;

// left motor
const int PWMA = 6;
const int AIN1 = 7;
const int AIN2 = 8;
// right motor
const int PWMB = 11;
const int BIN1 = 12;
const int BIN2 = 13;

void setup() {
  Serial.begin(9600);

  // SRF05 pin configuration
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  
  // motors pins configuration
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  // default configuration
  analogWrite(PWMA, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMB, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void loop() {

    #ifdef ULTRASONIC
    
    // auto run mode
    calculateDistance();
    if ((int)distance <= MAX_DISTANCE) {
      #ifdef DEBUG
      Serial.println("Near obstacle!!!");
      #endif
      stopMotors();
      delay(500);
      goBackward();
      delay(BACKWARD_DELAY);
      turnLeft();
      delay(TURN_LEFT_DELAY);
    } else {
      #ifdef DEBUG
      Serial.println("Going straight!!!");
      #endif
      goStraight();
    }
    
   #else
   
      #ifdef DEBUG
      Serial.println("Going straight!!!");
      #endif
      goStraight();
      
   #endif
  delay(100);
}

void stopMotors() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 0);
}

void goStraight() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, TARGET_SPEED);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, TARGET_SPEED);
}

void goBackward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, TARGET_SPEED);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, TARGET_SPEED);
}

void turnLeft() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, TARGET_SPEED);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, TARGET_SPEED);
}

void turnRight() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, TARGET_SPEED);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, TARGET_SPEED);
}

// read distance from SRF05 sensor
void calculateDistance() {
  unsigned long duration;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 29 / 2;
  
#ifdef DEBUG
  Serial.print("Distance in cm: ");
  Serial.println(distance);
#endif 
}
