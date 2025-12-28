#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "Wokwi-GUEST";
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
// setup wifi
  WiFi.begin(ssid);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
//setup lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Sending http request");

    HTTPClient http;

    String server = String("http://") + MAC_IP + ":8080/health";
    http.begin(server);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print("Json parse error: ");
        Serial.println(error.c_str());
        http.end();
        return;
      }
      lcd.setCursor(0, 0);
      lcd.print(httpResponseCode);
      String title = doc["key"];
      lcd.setCursor(0, 1);
      lcd.print(title);
      Serial.println("Success");
    } else {
      Serial.print("Error on http request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }

  delay(10000);
}
