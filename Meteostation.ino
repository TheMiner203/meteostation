// Метеостанция - https://github.com/TheMiner203/meteostation-arduino/
// OLED SCL - A5
// OLED SDA - A4

#define DHTPIN A3       // Пин, к которому подключен датчик
#define DHTMODEL DHT11  // Модель датчика (DHT11 или DHT22)
#include "DHT.h"        // Библиотека датчика DHT
#include <GyverOLED.h>  // Библиотека OLED экрана

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;  // Создать объект OLED экрана
DHT dht(DHTPIN, DHTMODEL);                       // Создать объект датчика DHT

float temperature, humidity;  // Создать переменные для температуры и влажности
bool isError;                 // Создать переменную для состояния ошибки

void setup() {
  dht.begin();         // Запустить датчик DHT
  oled.init();         // Запустить OLED экран
  Serial.begin(9600);  // Открыть порт на скорости 9600
  start();             // Очистить экран и вывести надписи
}

void loop() {
  float humidity = dht.readHumidity();        // Считать влажность и задать переменной humidity результат
  float temperature = dht.readTemperature();  // Считать температуру и задать переменной temperature результат

  if (isError && (!isnan(humidity) || !isnan(temperature))) {  // Если режим ошибки включен, но все данные считываются
    isError = false;                                           // Отключить режим ошибки
    start();                                                   // И заново вывести надписи
  }

  if (isnan(humidity) || isnan(temperature)) {  // Если данные не получается считать
    if (!isError) oled.clear();                 // Если режим ошибки выключен, т.е это первое обнаружение ошибки очистить экран
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
    Serial.print("Temperature:");
    Serial.println(temperature, 1);
    Serial.print("Humidity:");
    Serial.println(humidity, 1);
    oled.setCursorXY(60, 0);
    oled.print(temperature, 1);
    oled.print("C");
    oled.setCursorXY(60, 40);
    oled.print(humidity, 1);
    oled.print("%");
    delay(2000);
  }
}

void start() {
  oled.clear();          // Очистить экран
  oled.home();           // Вернуть курсор на начальную точку
  oled.setScale(2);      // Установить размер текста на 2
  oled.print("Темп:");   // Вывести надпись "Темп:"
  oled.setCursor(0, 5);  // Переместить курсор ниже
  oled.print("Влаж: ");  // Вывести надпись "Влаж:"
}
