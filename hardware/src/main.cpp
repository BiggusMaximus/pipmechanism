#include <Arduino.h>
#include "kalman.h"
#include "sensor.h"


void setup(){
    Serial.begin(115200);
    sensorInit();
}

void loop(){
    statsVoltage(500);
    // statsCurrent(500);
}