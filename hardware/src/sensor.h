#include <Arduino.h>
#include <Filters.h>
#include <RunningStats.h>
#include "math.h"
#define VOLTAGE_SENSOR 34
#define CURRENT_SENSOR 35

float sum, mean, standard_deviation, uncertainty;
float voltage, current, power;
float testFrequency = 50;                     // frekuensi sinyal (Hz)
float windowLength = 40.0/testFrequency;   


void sensorInit(){
    pinMode(VOLTAGE_SENSOR, INPUT);
    pinMode(CURRENT_SENSOR, INPUT);
}

float voltageMean_ADC(float NUMBER_OF_SAMPLES = 100){
    sum = 0;
    for (size_t i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        sum += analogRead(VOLTAGE_SENSOR);
    }
    return sum / NUMBER_OF_SAMPLES;
}

float currentMean_ADC(float NUMBER_OF_SAMPLES = 100){
    sum = 0;
    for (size_t i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        sum += analogRead(CURRENT_SENSOR);
    }
    return sum / NUMBER_OF_SAMPLES;
}

float voltageSTD(float mean, float NUMBER_OF_SAMPLES = 100){
    sum = 0;
    for (size_t i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        sum += pow(analogRead(VOLTAGE_SENSOR)-mean, 2);
    }
    return pow(sum / (NUMBER_OF_SAMPLES-1), 0.5);
}

float calibratedVoltage(float b1, float b0){
    return voltageMean_ADC() * b1 + b0;
}

float calibratedCurrent(float b1, float b0){
    return voltageMean_ADC() * b1 + b0;
}

float currentSTD(float mean, float NUMBER_OF_SAMPLES = 100){
    sum = 0;
    for (size_t i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        sum += pow(analogRead(CURRENT_SENSOR)-mean, 2);
    }
    return pow(sum / (NUMBER_OF_SAMPLES-1), 0.5);
}

float uncertaintyVoltage(float mean, float NUMBER_OF_SAMPLES = 100){
    sum = 0;
    for (size_t i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        sum += pow(analogRead(VOLTAGE_SENSOR)-mean, 2);
    }
    return pow(sum /(NUMBER_OF_SAMPLES * (NUMBER_OF_SAMPLES-1)), 0.5);
}

float uncertaintyCurrent(float mean, float NUMBER_OF_SAMPLES = 100){
    sum = 0;
    for (size_t i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        sum += pow(analogRead(CURRENT_SENSOR)-mean, 2);
    }
    return pow(sum /(NUMBER_OF_SAMPLES * (NUMBER_OF_SAMPLES-1)), 0.5);
}

void statsVoltage(float NUMBER_OF_SAMPLES = 100){
    mean = 0;
    standard_deviation = 0;
    uncertainty = 0;

    mean = voltageMean_ADC(NUMBER_OF_SAMPLES);
    standard_deviation = voltageSTD(mean, NUMBER_OF_SAMPLES);
    uncertainty = uncertaintyVoltage(mean, NUMBER_OF_SAMPLES);
    Serial.println("Mean : " + String(mean, 2) + " | STD : " + String(standard_deviation, 2) + " | Voltage : " + String(mean, 2) + " ± " + String(uncertainty, 2));
}

void statsCurrent(float NUMBER_OF_SAMPLES = 100){
    mean = 0;
    standard_deviation = 0;
    uncertainty = 0;

    mean = currentMean_ADC(NUMBER_OF_SAMPLES);
    standard_deviation = currentSTD(mean, NUMBER_OF_SAMPLES);
    uncertainty = uncertaintyCurrent(mean, NUMBER_OF_SAMPLES);
    Serial.println("            | Mean : " + String(mean, 2) + " | STD : " + String(standard_deviation, 2) + " | Current : " + String(mean, 2) + " ± " + String(uncertainty, 2));
}

float *calculate(float b1_v, float b0_v, float b1_i, float b0_i){
    RunningStats voltageStats;
    RunningStats currentStats;
    voltageStats.setWindowSecs(windowLength);
    currentStats.setWindowSecs(windowLength);
    voltageStats.input(voltageMean_ADC());
    currentStats.input(currentMean_ADC());
    float currentVolts = b0_v + b1_v * voltageStats.sigma();
    float currentAmps = b0_i + b1_i * (currentStats.sigma()); // Mengurangi offset tengah
    
    if (currentVolts < 0) {
    currentVolts = 0;
    }
    if (currentAmps < 0) {
    currentAmps = 0;
    }

    float power = currentVolts * currentAmps;
    static float data[3] = {currentVolts, currentAmps, power};

    return data;
}