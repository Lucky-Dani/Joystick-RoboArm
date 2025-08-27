#include <Servo.h>

Servo myServoX;
Servo myServoY;
Servo myServoZ;
Servo myServoLast;

const int joystickX = A0;
const int joystickY = A1;
const int joystickZ = A2;
const int joystickW = A3;
const int joystickButton = 4;

int posX = 90, posY = 50, posZ = 90, posLast = 90;
bool buttonState = false, lastButtonState = false;
bool isMoved = false;

void setup() {
    myServoX.attach(9);
    myServoY.attach(10);
    myServoZ.attach(11);
    myServoLast.attach(6);
    
    myServoX.write(posX);
    myServoY.write(posY);
    myServoZ.write(posZ);
    myServoLast.write(posLast);
    
    pinMode(joystickX, INPUT);
    pinMode(joystickY, INPUT);
    pinMode(joystickZ, INPUT);
    pinMode(joystickW, INPUT);
    pinMode(joystickButton, INPUT_PULLUP);
    
    Serial.begin(9600);
}

void loop() {
    int xValue = analogRead(joystickX);
    int yValue = analogRead(joystickY);
    int zValue = analogRead(joystickZ);
    int wValue = analogRead(joystickW);

    int newX = map(xValue, 0, 1023, 0, 180);
    int newY = map(yValue, 0, 1023, 100, 0);
    int newZ = map(wValue, 0, 1023, 45, 135);

    if (abs(newX - posX) > 2) posX += (newX > posX) ? 1 : -1;
    if (abs(newY - posY) > 2) posY += (newY > posY) ? 1 : -1;
    if (abs(newZ - posZ) > 2) posZ += (newZ > posZ) ? 1 : -1;

    myServoX.write(posX);
    myServoY.write(posY);
    myServoZ.write(posZ);
    
    buttonState = digitalRead(joystickButton);
    if (buttonState == LOW && lastButtonState == HIGH) {
        isMoved = !isMoved;
        posLast = isMoved ? 140 : 90;
    }
    lastButtonState = buttonState;
    myServoLast.write(posLast);
    
    delay(15);
}