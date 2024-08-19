#include <Servo.h>

const int trig = 2;
const int echo = 3;
const int trigLS = 4;
const int echoLS = 5;
const int trigRS = 6;
const int echoRS = 7;
const int servo = 10;
const int motor1 = 8;
const int motor2 = 9;
const int enable = 11;
const int maxDist = 10;
const int maxDistance = 10;

Servo myServo;

long distance;
long duration;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trigLS, OUTPUT);
  pinMode(echoLS, INPUT);
  pinMode(trigRS, OUTPUT);
  pinMode(echoRS, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(enable, OUTPUT);
  myServo.attach(servo);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  if (distance <= maxDist) {
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    analogWrite(enable, 0);
  } else {
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    analogWrite(enable, 150);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(200);

  digitalWrite(trigLS, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLS, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLS, LOW);
  long durationLeft = pulseIn(echoLS, HIGH);
  int distanceLeft = durationLeft * 0.034 / 2;

  digitalWrite(trigRS, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRS, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRS, LOW);
  long durationRight = pulseIn(echoRS, HIGH);
  int distanceRight = durationRight * 0.034 / 2;

  int steeringAngle = map(distanceLeft - distanceRight, -maxDistance, maxDistance, -90, 90);
  steeringAngle = constrain(steeringAngle, -90, 90);

  myServo.write(90 + steeringAngle);

  Serial.print("Left: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right: ");
  Serial.print(distanceRight);
  Serial.println(" cm");

  delay(200);
}
