
---
<div style="page-break-after: always;"></div>
---

Jakub Achtelik
Kacper Oborzyńśki

Koszalin, 06.06.2023

Platforma: Arduino C++
Temat: **Temat: Odczyt temperatury z czunika DS18B20, wyświetalnie jej na ekranie LCD, wykorzystanie endokera do ustawienia progu temperatury maksymalnej i minimalnej, zapewnienie sygnalizacji przekroczenia progu.**


Projekt na symulatorze:
https://wokwi.com/projects/366731957281831937

# 1. Wykorzystane biblioteki zewnętrzne
- Encoder
- OneWire
- DallasTemperature!
- LiquidCrystal

# 2. Utworzone klasy

Klasy w języku C++, utworzone do obłsugi projektu

## 2 .1 Obsługa wyświetlacza LCD 20x4
lcd.cpp

## 2.2 Miernik temperatury DS18B20

ds18b20.cpp

## 2.3 Endkoder

myencoder.cpp
