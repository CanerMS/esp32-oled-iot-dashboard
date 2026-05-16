# ESP32 OLED IoT Dashboard

## Hardware Prototype

The ESP32 is connected to the SSD1306 OLED display over I2C.

| OLED Pin | ESP32 Pin |
|----------|-----------|
|   VCC.   |    3V3    |
|   GND    |    GND    |
|   SDA    |   GPIO21  |
|   SCL.   |   GPIO22  |

## ESP32 Model

![ESP32 output](docs/images/esp32.jpg)

## OLED OUTPUT

![OLED Subscriber Output](docs/images/oled-output1.jpg)
![OLED Weather Output](docs/images/oled-output2.jpg)

## Learning Notes

This project was built step by step to understand:
- I2C communication between ESP32 and SSD1306 OLED
- basic OLED rendering and display buffering
- non-blocking timing with millis()
- Wi-Fi connection handling on ESP32
- HTTP requests and JSON parsing on a microcontroller