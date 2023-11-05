#include <Arduino.h>
#include "kalman.h"
#include "sensor.h"
#include "send.h"

unsigned long previousMillis = 0, currentMillis = 0;
const long interval = 5000; 

void setup(){
    Serial.begin(115200);
    sensorInit();
    wifiInit();
}

void loop(){
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        // voltage = calibratedVoltage(0.706, 0);
        // current = calibratedCurrent(0.00350, 0);
        // power = voltage * current;
        // sendData(power, current, power);
        
        float *data = calculate(0.706, 0, 0.00350, 0);
        sendData(data[0], data[1], data[2]);
    }
}