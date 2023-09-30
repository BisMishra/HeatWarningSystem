#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Replace with your OpenWeatherMap API key
const char* apiKey = "Your_API_KEY";

// Your city and country (e.g., "City, Country Code")
const char* location = "Your_City,Country_Code";

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address may vary; use the correct address for your LCD

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // Check for weather alerts
  String weatherAlerts = getWeatherAlerts();

  // Display alerts on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weather Alerts:");
  lcd.setCursor(0, 1);
  lcd.print(weatherAlerts);

  // Wait before checking again (adjust as needed)
  delay(600000); // Wait for 10 minutes before checking again
}

String getWeatherAlerts() {
  String alerts = "";

  // Create a URL for the OpenWeatherMap API request
  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + String(location) + "&appid=" + apiKey;

  // Send HTTP GET request to OpenWeatherMap
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();

    // Parse JSON data using ArduinoJSON library
    const size_t capacity = JSON_OBJECT_SIZE(1) + 200;
    DynamicJsonDocument jsonDoc(capacity);
    deserializeJson(jsonDoc, payload);

    // Check if there are any alerts
    JsonObject alertsObj = jsonDoc["alerts"];
    if (!alertsObj.isNull()) {
      // Extract alert information
      alerts = alertsObj[0]["description"].as<String>();
    }
  }

  http.end();
  return alerts;
}