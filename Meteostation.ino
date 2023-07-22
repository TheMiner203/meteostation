// Метеостанция
// OLED SCL - A5
// OLED SDA - A4
#define DHTPIN A3
#include "DHT.h"
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
DHT dht(DHTPIN, DHT11);

void setup() {
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
  oled.clear();
  oled.home();
  oled.setScale(2);
  oled.print("Темп:");
  oled.setCursor(0, 5);
  oled.print("Влаж: ");
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    oled.clear();
    oled.home();
    oled.print("Ошибка");
    oled.setScale(1);
    oled.setCursor(0, 3);
    oled.print("Подключите датчик и");
    oled.setCursor(0, 5);
    oled.print("перезагрузите устрой-");
    oled.setCursor(0, 7);
    oled.print("ство");
    while (true)  //бесконечное ожидание
    return;
  }
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
  //asm volatile("jmp 0x00");
}
