# ESP32 OLED IoT Dashboard

## Hardware Prototype

The ESP32 is connected to the SSD1306 OLED display over I2C.

| OLED Pin | ESP32 Pin |
|----------|-----------|
|   VCC.   |    3V3    |
|   GND    |    GND    |
|   SDA    |   GPIO21  |
|   SCL.   |   GPIO22  |

- ESP32 DevKit / NodeMCU ESP32
- SSD1306 128x64 I2C OLED display
- Jumper wires
- USB-C cable

## ESP32 Model

![ESP32 output](docs/images/esp32.jpg)

## OLED OUTPUT

![OLED Subscriber Output](docs/images/oled-output1.jpg)
![OLED Weather Output](docs/images/oled-output2.jpg)

## Current Status

The current version supports:
- SSD1306 OLED display over I2C
- Static YouTube subscriber screen
- Static weather forecast screen
- Non-blocking screen switching using `millis()`
- Secure Wi-Fi configuration using a local `secrets.h` file
- Wi-Fi connection test with OLED status output

## Secure Configuration

Wi-Fi credentials are not stored directly inside `main.cpp`.

Create a local file:

```text
include/secrets.h
```

## Learning Notes

This project was built step by step to understand:
- I2C communication between ESP32 and SSD1306 OLED
- basic OLED rendering and display buffering
- non-blocking timing with millis()
- Wi-Fi connection handling on ESP32
- HTTP requests and JSON parsing on a microcontroller