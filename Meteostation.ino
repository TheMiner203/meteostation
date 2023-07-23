// Метеостанция
// OLED SCL - A5
// OLED SDA - A4
#define DHTPIN A3       // Пин, к которому подключен датчик
#define DHTMODEL DHT11  // Модель датчика (DHT11 или DHT22)
#include "DHT.h"
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
DHT dht(DHTPIN, DHTMODEL);
bool isError;
float t;
float h;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  dht.begin();
  oled.init();
  Serial.begin(9600);
  oled.clear();
  oled.home();
  oled.setScale(3);
  oled.print("Метео -");
  oled.setCursor(0, 4);
  oled.print("станция");
  delay(1500);
  start();
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isError == true && (!isnan(h) || !isnan(t))) {
    isError = false;
    oled.clear();
    start();
  }
  if (isnan(h) || isnan(t)) {
    if (isError == false) {
      oled.clear();
    }
    oled.home();
    oled.setScale(2);
    oled.print("Ошибка");
    oled.setScale(1);
    oled.setCursor(0, 3);
    oled.print("Подключите датчик");
    oled.setCursor(0, 5);
    oled.print("DHT");
    oled.print(DHTMODEL);
    oled.print(" к пину ");
    oled.print(DHTPIN);
    oled.setScale(1);
    isError = true;
  }
  if (isError == false) {
    Serial.print(t);
    Serial.print(',');
    Serial.println(h);
    oled.setCursorXY(60, 0);
    oled.print(t, 1);
    oled.print("C");
    oled.setCursorXY(60, 40);
    oled.print(h, 1);
    oled.print("%");
    delay(2000);
  }
}
void start() {
  oled.clear();
  oled.home();
  oled.setScale(2);
  oled.print("Темп:");
  oled.setCursor(0, 5);
  oled.print("Влаж: ");
}
