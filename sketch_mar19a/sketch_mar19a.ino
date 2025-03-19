#include <Wire.h>                      // Подключаем библиотеку для работы с I2C
#include <LiquidCrystal_I2C.h>          // Библиотека для I2C LCD дисплея
#include <DHT.h>                        // Библиотека для работы с датчиком DHT

#define DHTPIN 2                        // Пин, к которому подключен DHT22
#define DHTTYPE DHT22                   // Указываем тип датчика DHT22

DHT dht(DHTPIN, DHTTYPE);               // Инициализация датчика
LiquidCrystal_I2C lcd(0x3F, 16, 2);     // Инициализация LCD дисплея: 0x27 — адрес дисплея (замените при необходимости)

void setup() {
  lcd.init();                           // Инициализация дисплея
  lcd.backlight();                      // Включение подсветки LCD
  dht.begin();                          // Запуск датчика DHT
}

void loop() {
  // Чтение температуры и влажности
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Проверка, удалось ли получить данные
  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ошибка датчика");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Влажность: ");
    lcd.print(humidity);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("Температура: ");
    lcd.print(temperature);
    lcd.print("C");
  }

  delay(2000); // Обновление данных каждые 2 секунды
}