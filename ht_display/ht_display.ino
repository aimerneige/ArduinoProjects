/**
 * Author:
 *     Name:    Aimer Neige
 *     Email:   aimer.neige@aimerneige.com
 *     Website: https://aimerneige.com
 *     GitHub:  https://github.com/AimerNeige
 *
 * Hardware:
 *     esp32
 *     ssd1306 128*64
 *     aht10
 *     led
 *     resistor
 *     breadboard
 *     Breadboard Jumpers
 *
 * SSD1306:    GND   VCC   D0   D1   RES   DC   CS
 * ESP32:      GND   3V3   18   23   TX2   RX2  5
 *
 * ATH10:      GND   VCC   SCL   SDA
 * ESP32:      GND   3V3   22    21
 *
 * LED:        +     -   (Do not forget to add a resistor)
 * ESP32:      33    GND
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHT10.h>

Adafruit_AHT10 aht; // AHT10 Sensor

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI
#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17

// SSD1306 OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// LED light
#define LED  33

// Temprature
#define temp_threshold 28

// setup ssd1306 display
void setupDisplay() {
  Serial.println("Start Setup SSD1306!");
  if(! display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    // loop forever
    while (1) {
      delay(10);
    }
  }
  display.clearDisplay();
  display.display();
  delay(1000);
  Serial.println("SSD1306 Setup Seccessful!");
}

// setup aht10 sensor
void setupAHT10() {
  Serial.println("Start Setup AHT10!");
  if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) {
      // loop forever
      delay(10);
    }
  }
  Serial.println("AHT10 Setup Successful!");
}

// setup led
void setupLED() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void setup() {
  Serial.begin(115200);
  setupAHT10();
  setupDisplay();
  setupLED();
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  if (temp.temperature > temp_threshold) {
    lightLED();
  } else {
    offLED();
  }

  String disTemp = "Temprature: " + String(temp.temperature) + " C";
  String disHumi = "Humidity: " + String(humidity.relative_humidity) + "% rH";
  String ledStat = "LED: " + String(digitalRead(LED) ? "ON" : "OFF");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Copyright (c) 2022");
  display.println("by Aimer Neige");
  display.println("All rights reserved");
  display.println(disTemp);
  display.println(disHumi);
  display.println(ledStat);
  display.display();

  delay(500);
}

void lightLED() {
  digitalWrite(LED, HIGH);
}

void offLED() {
  digitalWrite(LED, LOW);
}
