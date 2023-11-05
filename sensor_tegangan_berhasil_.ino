#include <Filters.h>

float testFrequency = 50;                     // frekuensi sinyal (Hz)
float windowLength = 40.0/testFrequency;     // berapa lama rata-rata sinyal, untuk statistik

int sensorVoltagePin = 34; // Pin untuk membaca tegangan dari sensor ZMPT101B
int sensorCurrentPin = 35; // Pin untuk membaca arus dari sensor SCT-013

int analogVoltageValue;
int analogCurrentValue;

float interceptVoltage = 0;  // penyesuaian kalibrasi
float slopeVoltage = 0.706;   // penyesuaian kalibrasi
float interceptCurrent = 0.0;   // Anda harus mengkalibrasi ini sesuai dengan karakteristik sensor SCT-013 Anda
float slopeCurrent = 0.00350;       // Anda harus mengkalibrasi ini sesuai dengan karakteristik sensor SCT-013 Anda

float currentVolts; 
float currentAmps;

unsigned long printPeriod = 1000; // periode refresh
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("AC Power Meter");
}

void loop() {
  RunningStatistics voltageStats;
  RunningStatistics currentStats;
  voltageStats.setWindowSecs(windowLength);
  currentStats.setWindowSecs(windowLength);

  while (true) {
    int sensorVoltage = analogRead(sensorVoltagePin);
    int sensorCurrent = analogRead(sensorCurrentPin);
    
    // Pastikan tegangan dan arus tidak pernah kurang dari 0
    if (sensorVoltage < 0) {
      sensorVoltage = 0;
    }
    if (sensorCurrent < 0) {
      sensorCurrent = 0;
    }

    analogVoltageValue = sensorVoltage;  // Baca nilai analog dari pin sensor tegangan
    analogCurrentValue = sensorCurrent;  // Baca nilai analog dari pin sensor arus

    voltageStats.input(sensorVoltage);
    currentStats.input(sensorCurrent);

    if ((unsigned long)(millis() - previousMillis) >= printPeriod) {
      previousMillis = millis();

      currentVolts = interceptVoltage + slopeVoltage * voltageStats.sigma();
      currentAmps = interceptCurrent + slopeCurrent * (currentStats.sigma()); // Mengurangi offset tengah
      
      if (currentVolts < 0) {
        currentVolts = 0;
      }
      if (currentAmps < 0) {
        currentAmps = 0;
      }

      float power = currentVolts * currentAmps;

      Serial.print("Voltage: ");
      Serial.print(currentVolts, 2);
      Serial.print(" V\t");

      Serial.print("Current: ");
      Serial.print(currentAmps, 2);
      Serial.print(" A\t");

      Serial.print("Power: ");
      Serial.print(power, 2);
      Serial.print(" W\t");

      Serial.print("Analog Voltage: ");
      Serial.print(analogVoltageValue); // Mencetak nilai analog dari pin sensor tegangan
      Serial.print("\tAnalog Current: ");
      Serial.println(analogCurrentValue); // Mencetak nilai analog dari pin sensor arus
    }
  }
}
