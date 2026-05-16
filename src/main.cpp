#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not found.");
    while (true) {
      delay(1000);
    }
  }

  drawYoutubeScreen();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSwitchTime >= SCREEN_INTERVAL) {
    showYoutubeScreen = !showYoutubeScreen;
    lastSwitchTime = currentTime;

    if (showYoutubeScreen) {
      drawYoutubeScreen();
    } else {
      drawWeatherScreen();
    }
  }
}
