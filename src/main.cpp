#include <Arduino.h>
#include <Wire.h>  
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

// Wifi Connection
#include <WiFi.h>

// Secure client
#include <WiFiClientSecure.h> // for TLS requirement and data safety

// HTTP
#include <HTTPClient.h> // HTTP steps ex: GET/POST



// The WiFi Info
#include "secrets.h" 

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_RESET -1
#define OLED_ADDR 0x3C

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 10 seconds = 10 ms
const unsigned long SCREEN_INTERVAL = 5000;

unsigned long lastSwitchTime = 0;
bool showYoutubeScreen = true;




void drawYoutubeScreen() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Youtube");

  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setCursor(0, 25);
  display.println("4500");

  display.setTextSize(1);
  display.setCursor(0, 55);
  display.println("Subscribers");

  display.display();
}

void drawWeatherScreen() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Weather Today");

  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  display.setCursor(0, 20);
  display.println("09:00 12C Cloudy");

  display.setCursor(0, 34);
  display.println("15:00 15C Rain");

  display.setCursor(0, 48);
  display.println("18:00 12C Snowy");

  display.display();
}



void drawText(const String& line1, const String& line2, const String& line3, const String& line4) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println(line1);

  display.setCursor(0, 16);
  display.println(line2);

  display.setCursor(0, 32);
  display.println(line3);

  display.setCursor(0, 48);
  display.println(line4);

  display.display();
}

void connectWiFi() {
  drawText("WiFi", "Connecting...", "", "");

  Serial.print("Connecting to WiFi:");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int tries = 0;

  while (WiFi.status() != WL_CONNECTED && tries < 30) {
    delay(500);
    Serial.print(".");
    tries++;

    drawText(
      "WiFi connecting",
      "Try: " + String(tries),
      "Please wait...",
      ""
    );
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("IP adress: ");
    Serial.println(WiFi.localIP());
  
    drawText(
      "Wifi Connected",
      "IP:",
      WiFi.localIP().toString(),
      "Ready"
    );
  } else {
    Serial.println("WiFi failed");

    drawText(
      "Wifi Failed",
      "Check SSID",
      "Check password",
      "Use 2.4 GHz"
    );
  }
}

void fetchWeatherJson() {
  WiFiClientSecure client;
  HTTPClient http;
  DeserializationError error;
  client.setInsecure();

  // URL
  String url = 
    "https://api.open-meteo.com/v1/forecast"
    "?latitude=50.7753"
    "&longitude=6.0839"
    "&hourly=temperature_2m,weather_code"
    "&timezone=Europe%2FBerlin" // %2F is the URL encoded form of '/'
    "&forecast_days=1";

  // GET
  http.begin(client, url);

  int httpCode = http.GET();

  Serial.print("HTTP status: ");
  Serial.println(httpCode);

  if (httpCode==200) {
    String payload = http.getString();
    Serial.println(payload);

    JsonDocument doc;

    

    error = deserializeJson(doc, payload);

    // error : boolean  
    if (error) {
      Serial.print("JSON parse failed: ");
      Serial.println(error.c_str()); // c_str() gives you the error as a text
      return;
    } else {
      JsonArray times = doc["hourly"]["time"];
      JsonArray temperatures = doc["hourly"]["temperature_2m"];
      JsonArray weatherCodes = doc["hourly"]["weather_code"];


      const char* firstTime = times[0].as<const char*>(); // avoid mismatch for else condition
      float firstTemperature = temperatures[0].as<float>();
      int firstWeatherCode = weatherCodes[0].as<int>();
      
      Serial.println(firstTime);
      Serial.println(firstTemperature);
      Serial.println(firstWeatherCode);   
  }
  http.end();
  } 
}

void setup() {


  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not found.");
    while (true) {
      delay(1000);
    }
  }

  drawText("ESP32 Boot", "OLED ok", "Starting WiFi", "");

  delay(1000);
  connectWiFi();
  fetchWeatherJson();
}

void loop() {
}
