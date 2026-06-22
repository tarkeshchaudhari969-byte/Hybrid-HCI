#include <Arduino.h>
#include <Wire.h>
#include <BleMouse.h>

#define MPU_ADDR 0x68

// Buttons
#define LEFT_BUTTON 18
#define RIGHT_BUTTON 19
#define RECENTER_BUTTON 23

BleMouse bleMouse;

// Bias
float gyroBiasX = 0;
float gyroBiasZ = 0;

// Settings
float smoothing = 0.9;
float sensitivity = 1.2;
float deadzone = 0.8;

// Smoothing variables
float fX = 0;
float fZ = 0;

// Button timing
unsigned long leftPressStart = 0;
unsigned long rightPressStart = 0;
bool leftHeld = false;
bool rightHeld = false;

const int clickThreshold = 250;
const int scrollDelay = 50;
unsigned long lastScrollTime = 0;

// Recenter logic
unsigned long recenterPressStart = 0;
const int freezeThreshold = 400;

// Read MPU
int16_t read16(uint8_t reg) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.endTransmission(true);
    Wire.requestFrom(MPU_ADDR, (uint8_t)2);
    return (Wire.read() << 8) | Wire.read();
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(RECENTER_BUTTON, INPUT_PULLUP);

    Wire.begin(21, 22);
    Wire.setClock(50000);

    // Wake MPU
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);

    delay(100);

    // Calibration
    Serial.println("Calibrating... Keep still!");
    for (int i = 0; i < 500; i++) {
        gyroBiasX += read16(0x43);
        gyroBiasZ += read16(0x47);
        delay(5);
    }

    gyroBiasX /= 500;
    gyroBiasZ /= 500;

    Serial.println("Calibration done");

    delay(2000);
    bleMouse.begin();
    Serial.println("BLE started");
}

void loop() {
    if (!bleMouse.isConnected()) return;

    unsigned long now = millis();

    // -------- RECENTER / FREEZE --------
    bool freezeCursor = false;

    if (digitalRead(RECENTER_BUTTON) == LOW) {

        if (recenterPressStart == 0) {
            recenterPressStart = now;
        }

        // Long press → freeze
        if (now - recenterPressStart >= freezeThreshold) {
            freezeCursor = true;
        }

    } else if (recenterPressStart != 0) {

        // Short press → re-center
        if (now - recenterPressStart < freezeThreshold) {
            fX = 0;
            fZ = 0;
            Serial.println("Re-centered!");
        }

        recenterPressStart = 0;
    }

    // -------- LEFT BUTTON --------
    if (digitalRead(LEFT_BUTTON) == LOW) {

        if (leftPressStart == 0) {
            leftPressStart = now;
            leftHeld = false;
        }

        if (!leftHeld && now - leftPressStart >= clickThreshold)
            leftHeld = true;

        if (leftHeld && now - lastScrollTime >= scrollDelay) {
            bleMouse.move(0, 0, 1);
            lastScrollTime = now;
            return;
        }

    } else if (leftPressStart != 0) {

        if (!leftHeld && now - leftPressStart < clickThreshold)
            bleMouse.click(MOUSE_LEFT);

        leftPressStart = 0;
        leftHeld = false;
    }

    // -------- RIGHT BUTTON --------
    if (digitalRead(RIGHT_BUTTON) == LOW) {

        if (rightPressStart == 0) {
            rightPressStart = now;
            rightHeld = false;
        }

        if (!rightHeld && now - rightPressStart >= clickThreshold)
            rightHeld = true;

        if (rightHeld && now - lastScrollTime >= scrollDelay) {
            bleMouse.move(0, 0, -1);
            lastScrollTime = now;
            return;
        }

    } else if (rightPressStart != 0) {

        if (!rightHeld && now - rightPressStart < clickThreshold)
            bleMouse.click(MOUSE_RIGHT);

        rightPressStart = 0;
        rightHeld = false;
    }

    // -------- GYRO --------
    float rotX = (read16(0x43) - gyroBiasX) / 131.0;
    float rotZ = (read16(0x47) - gyroBiasZ) / 131.0;

    // -------- SMOOTHING --------
    fX = fX * smoothing + rotX * (1 - smoothing);
    fZ = fZ * smoothing + rotZ * (1 - smoothing);

    // -------- MOVEMENT --------
    float moveXf = -(fZ * sensitivity);
    float moveYf = (fX * sensitivity);

    if (abs(fZ) < deadzone) moveXf = 0;
    if (abs(fX) < deadzone) moveYf = 0;

    int moveX = (int)moveXf;
    int moveY = (int)moveYf;

    if (!freezeCursor && (moveX || moveY)) {
        bleMouse.move(moveX, moveY);
    }

    delay(5);
}