#include <NewPing.h>

// Motor Driver Pins
const int LeftMotorForward = 8;
const int LeftMotorBackward = 9;
const int RightMotorForward = 10;
const int RightMotorBackward = 11;

// Ultrasonic Sensor Pins
#define trigPinFront A0
#define echoPinFront A1
#define trigPinLeft A2
#define echoPinLeft A3
#define trigPinRight A4
#define echoPinRight A5

#define maximum_distance 200
boolean goesForward = false;
int distanceFront = 100;
int distanceLeft = 100;
int distanceRight = 100;

NewPing sonarFront(trigPinFront, echoPinFront, maximum_distance);
NewPing sonarLeft(trigPinLeft, echoPinLeft, maximum_distance);
NewPing sonarRight(trigPinRight, echoPinRight, maximum_distance);

void setup() {
    // Initialize motor driver pins
    pinMode(RightMotorForward, OUTPUT);
    pinMode(LeftMotorForward, OUTPUT);
    pinMode(LeftMotorBackward, OUTPUT);
    pinMode(RightMotorBackward, OUTPUT);

    // Initialize sensor readings
    delay(2000); // Wait for sensors to stabilize
    distanceFront = readPingFront();
    distanceLeft = readPingLeft();
    distanceRight = readPingRight();
}

void loop() {
    delay(50); // Small delay for stability

    // Update distances
    distanceFront = readPingFront();
    distanceLeft = readPingLeft();
    distanceRight = readPingRight();

    if (distanceFront <= 20) {
        moveStop();
        delay(300);
        moveBackward();
        delay(400);
        moveStop();
        delay(300);

        if (distanceLeft > distanceRight) {
            turnLeft();
        } else {
            turnRight();
        }
    } else if (distanceLeft <= 15) {
        turnRight();
    } else if (distanceRight <= 15) {
        turnLeft();
    } else {
        moveForward(); 
    }
}

int readPingFront() {
    int cm = sonarFront.ping_cm();
    return (cm == 0) ? maximum_distance : cm;
}

int readPingLeft() {
    int cm = sonarLeft.ping_cm();
    return (cm == 0) ? maximum_distance : cm;
}

int readPingRight() {
    int cm = sonarRight.ping_cm();
    return (cm == 0) ? maximum_distance : cm;
}

void moveStop() {
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
    if (!goesForward) {
        goesForward = true;
        digitalWrite(LeftMotorForward, HIGH);
        digitalWrite(RightMotorForward, HIGH);
        digitalWrite(LeftMotorBackward, LOW);
        digitalWrite(RightMotorBackward, LOW); 
    }
}

void moveBackward() {
    goesForward = false;
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorForward, LOW);
    delay(300);
    moveForward();
}

void turnLeft() {
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    delay(300);
    moveForward();
}
