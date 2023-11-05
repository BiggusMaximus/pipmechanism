#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "BaseEngineering";
const char* password = "123456780";
const char* serverURL = "https://pipmechanism-monitoring-pkmkc.baseengineering-indonesia.com/api.php"; // Replace with your database API URL


void wifiInit() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void sendData(float voltage, float current, float power) {
  if (WiFi.status() == WL_CONNECTED) {
    // Create a JSON object with the float variables
    String data = "voltage=" + String(voltage, 2) + "&current=" + String(current, 2) + "&power=" + String(power, 2);
    Serial.println(data);
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(data);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response Code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}