
# LABOLATORIA SYSTEMÓW ELEKTRONICZNYCH

Koszalin, 06.06.2023

Autorzy: JAKUB ACHTELIK, KACPER OBORZYŃŚKI \
Temat: **MIERNIK TEMPERATURY 9**
1. Odczyt temperatury z czunika DS18B20
2. Wyświetalnie jej na ekranie LCD,
3. Wykorzystanie endokera do ustawienia progu temperatury maksymalnej i minimalnej,
4. Zapewnienie sygnalizacji przekroczenia progu.

Platforma: Arduino IDEE C/C++\
Projekt na symulatorze: https://wokwi.com/projects/366878180834874369

**SCHEMAT**\
<img src="https://i.ibb.co/937VctB/Screenshot-from-2023-06-08-15-28-31.png" />

# 1. Projekt 

**Wykorzystane komponenty**:
1. Miernik temperatury DS18B20
2. Wyświetlacz LCD 16x1
3. Enkoder
4. Czerwona Dioda LED
5. Przycisk

**Wykorzystane oprogramowanie**:
- Wokwi - symulator online
- Arduino IDEE 2.x

**Wykorzystane biblioteki zewnętrzne**:
- Standardowa biblioteka Arduino
- LiquidCrystal
- OneWire
- DallasTemperature
- Encoder

Udzielenie uprawnień przed zaprogramowaniem płytki dla systemu Ubutnu 22.04
```bash
sudo chmod a+rw /dev/ttyACM0  
```

# 2. Pliki źródłowe projektu

## Wywołanie metod
plik: main.ino, MiernikTemperatury9.cpp\
Plik main.ino zawiera główną klasę **MiernikTemperatury9**, która agreguje cały kod i wywołuje wszystkie metody.

## Plik konfiguracyjnych
plik: CONFIG.cpp\
Zawiera konfigurację wszystkich pinów oraz załącza wszystkie klasy.

## 2 .1 Wyświetlacza LCD 16x1
- klasa: ScreenLcd
- plik: SreenLcd.cpp
- biblioteka: LiquidCrystal.h, Arduino.h


## 2.2 Miernik temperatury DS18B20
klasa: TemperatureSensorDS18B20
plik: ds18b20.cpp
biblioteka: LiquidCrystal.h


## 2.3 Endkoder
klasa: myEncoder
plik: MyEncoder.cpp
biblioteka: OneWire.h , DallasTemperature.h

## 2.4 Przycisk
klasa: Button\
plik: Button.cpp\
biblioteka: Arduino.h


## 2.5 Dioda LED
klasa: DiodeLed
plik: DiodeLed.cpp
biblioteka: Arduino.h


# 3. Problematyka

## 3.1 Problem układu Raspberry Pi Pico W - RP2040
Wybór Arduino Uno zamiast Rasberry PI Pico W rozwiązał problem nie działającej obsługi czunika DS18B20. 
Biblioteka 'OneWire' powodowała błędy podczas wgrywania programu na układ Pico.
Po wielu nieudanych próbach udało się znaleźć odpowiednią obługę w MicroPython, jednak reszta założeń projektu tak jak obługa ekranu LCD, była dość złożona i powodowała problemy.
Płytka Arduino Uno, lepiej współpracowało ze środowiskiem Arduino IDEE, i czas wgyrwa oraz komplilacji był o wiele szybszy, co umożliwiło bardziej komfortową pracę.
\
\
\
Kod MicroPython do obsługi DB18B20:
```py
import machine, onewire, ds18x20, time
 
ds_pin = machine.Pin(21)

ds_sensor = ds18x20.DS18X20(onewire.OneWire(ds_pin))
roms = ds_sensor.scan()


def Temperatura(roms,ds_sensor):
  ds_sensor.convert_temp()
  time.sleep_ms(750)
  for rom in roms:
    temperatura = ds_sensor.read_temp(rom)
    print(f"Temperatura: {temperatura} C") 
  time.sleep(2)

 
while True:
    Temperatura(roms,ds_sensor)
```
\
\
\


## 3.2 OOP - Programowanie obiektowe
Dodatkowo w celu ułatwienia i utrzymania przejrzystości kodu wykorzystane zostało programoanie obiektowe i podział na klasy i obiekty w C++.

## 3.3 Podział plików
Wydzielenie różnych funkcjonalności do osobnych plików, które: 
- ułatwiają rozbudowe
- ułatwiają znalezienie błedu
- są skalowanlen, pliki można wykorzystać wielokrotnie w innym projekcie
## 3.4 Testowanie
W głównej klasie 'MiernikTemperatury9' znajduję się metoda "Testowanie()" w której można wywołać funkcję do testowania czy podłaczony element komunikuje się z Arduino.
Poprzez wywołanie na obiekcie metody **.test()**\
Przykład testowania czujnika:

```cpp
    void Testowanie()
    {
      // Serial.println("Test arduino is connect");
      TemperatureSensor.test();
      // Lcd.test();
      // MyEncoder.test();
      // Btn.test();
      // Led.test();
    }

    void loop() 
    {
      // Wyswietlacz();
      // SygnalizcajaProgu();
      Testowanie();
    }
```

