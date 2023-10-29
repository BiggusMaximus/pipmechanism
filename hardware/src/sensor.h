#include <Arduino.h>
#include "math.h"
#define VOLTAGE_SENSOR 35
#define CURRENT_SENSOR 12
float sum, mean, standard_deviation, uncertainty;

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