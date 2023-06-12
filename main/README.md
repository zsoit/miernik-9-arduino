
---
# CONFIG

# toc: true

title: "Miernik temperatury 9"
subtitle: "Labolatorium Systemów Elektronicznych"
author: "Autorzy: Jakub Achtelik, Kacper Oborzyński"
date: "Koszalin, 12 Czerwca 2023"
institute: "Politechnika Koszalińśka"
language: pl

# style-definition
geometry: margin=1in
highlight-style: monochrome
fontfamily: helvet

header-includes:
  - \renewcommand{\familydefault}{\sfdefault}
  - \usepackage{fancyhdr}
  - \pagestyle{fancy}
  - \fancyhead[LE,RO]{Labolatorium Systemów Elektronicznych}
  - \fancyfoot[CO,CE]{Achtelik, Oborzyński - Miernik temperatury 9}
  - \fancyfoot[LE,RO]{\thepage}
  - \renewcommand{\contentsname}{Spis treści}
  
  - \usepackage{titling}
  - \pretitle{\begin{center}\Huge\vspace*{\fill}}
  - \posttitle{\vspace*{\fill}\end{center}}
  
  - \usepackage{caption} 
  - \renewcommand{\figurename}{Rysunek}
---

\thispagestyle{empty} 
\newpage
\thispagestyle{empty} 
\tableofcontents{}
\newpage
	
# 1. Projekt

 **Temat: MIERNIK TEMPERATURY 9** \newline
1. Odczyt temperatury z czunika DS18B20 \newline
2. Wyświetlanie jej na ekranie LCD \newline
3. Wykorzystanie endokera do ustawienia progu temperatury maksymalnej i minimalnej \newline
4. Zapewnienie sygnalizacji przekroczenia progu \newline


Platforma: Arduino IDEE C/C++

Projekt na symulatorze: **https://wokwi.com/projects/367315813073881089**

## 1.1 Wykorzystane komponenty
- Arduino Uno
- Miernik temperatury DS18B20 + 2x rezystor 5k Ohm
-  Wyświetlacz LCD 20x4 
-  Enkoder
-  Czerwona Dioda LED + 1x rezystor 1k Ohm
-  Przycisk

## 1.2 Schemat podłączenia

### 1.2.1 Wyświetlacz LCD (Piny licząc od lewej):
1. GND - masa
2. Vcc - zasilanie dodatnie, 5V
3. V0 - regulacja kontrastu
4. RS - wybór rejestrów (komenda, dane)
5. RW - wybór opcji odczyt/zapis
6. E - zezwolenie na zapis do rejestrów
7. D0 - dane
8. D1 - dane
9. D2 - dane
10. D3 - dane
11. D4 - dane (używane)
12. D5- dane (używane)
13. D6 - dane (używane)
14. D7 - dane (używane)
15. Vpod - zasilanie dodatnie podświetlenia
16. GNDpod - masa podświetlenia

### 1.2.2 Miernik temperatury DS18B20 (Piny licząc od lewej):
1. GND masa
2. PIN sygnałowy
3. Vcc Zasilanie 5V

### 1.2.3 Dioda LED
1. Anoda (Dłuższą nóżka) - do GND - masy przez rezystor 
2. Katoda (Krótsza nóżka) - PIN sygnałowy

### 1.2.4 Enkoder (Piny licząc od lewej):
1. GND - masa
2. Vcc - zasilanie dodatnie 5v
3. SW - przycisk środkowy, PIN sygnałowy
4. SIB- PIN sygnałowy 
5. SIA - PIN sygnałowy

![Schemat podłączenia](https://jakub.hu1.pl/elektro/lcd20x4.jpg)

\newpage

## 1.3 Wykorzystane oprogramowanie
- Wokwi - symulator online
- Arduino IDE 2.1.0

## 1.4 Wykorzystane biblioteki zewnętrzne
- Standardowa biblioteka Arduino
- LiquidCrystal
- OneWire
- DallasTemperature
- Encoder

\newpage

# 2. Pliki źródłowe projektu

- main.ino
- MiernikTemperatury9.cpp
- CONFIG.cpp
- ds18b20.cpp
- SreenLcd.cpp
- MyEncoder.cpp
- DiodeLed.cpp

## 2.1 Inicjalizacja - main.ino 

```cpp
#include "MiernikTemperatury9.cpp"
MiernikTemperatury9 projekt;
void setup() {
  projekt.setup();
}
void loop() {
  projekt.loop();
}
```

## 2.2 Wywołanie metod -  MiernikTemperatury9.cpp

Plik  MiernikTemperatury9.cpp zawiera klasę  **MiernikTemperatury9**, która agreguje cały kod i wywołuje wszystkie metody.
```cpp
#include "CONFIG.cpp"
class MiernikTemperatury9 
{
  private:
    MyEncoder MyEncoder;
    TemperatureSensorDS18B20 TemperatureSensor;
    ScreenLcd Lcd;
    DiodeLed Led;
    Button Btn;    
    
  public:
    void Testowanie()
    {
      // Serial.println("Test - arduino is connect");
      // TemperatureSensor.test();
      // Lcd.test();
      // MyEncoder.test();
      // Btn.test();
      // Led.test();
    }

    void loop() 
    {
      Wyswietlacz();
      SygnalizcajaProgu();
      Testowanie();
    }

    void setup() 
    {
      Serial.begin(SERIAL_PORT);
      MyEncoder.setup();
      TemperatureSensor.setup();
      Lcd.setup();
    }

    MiernikTemperatury9() : 
      MyEncoder(ENCODER_A_PIN, ENCODER_B_PIN, RESET_BTN_PIN),
      TemperatureSensor(DS_PIN),
      Lcd(RS, E, D4, D5, D6, D7),
      Led(LED_PIN),
      Btn(BTN_PIN) {}

    void SygnalizcajaProgu() 
    {
      // SYGNALIZACJA PROGU  
      long limit = MyEncoder.getCounter();
      float limit_temperature = TemperatureSensor.readTemperature();
      limit_temperature = static_cast<int>(limit_temperature);
      int option = Btn.detectPress();
      if (option == 1)
        Led.limit_max(limit, limit_temperature);
      if (option == 0)
        Led.limit_min(limit, limit_temperature);
    }
    
    void Wyswietlacz() 
    {
      // ODCZYT TEMPERATURY
      float get_temperature = TemperatureSensor.readTemperature();
      long get_counter = MyEncoder.getCounter();
      float get_kelvin = TemperatureSensor.readKelvin();
      float get_fahrenheit = TemperatureSensor.readFahrenheit();
      
      // NAPISY
      String text_limit_header = Btn.text_limit();
      String text_limit = text_limit_header + String(get_counter) + " C";
      String text_temperature = "T:" + String(get_temperature) + " C";
      String text_kelvin = String(get_kelvin) + "K";
      String text_fahrenheit  = String(get_fahrenheit ) + "F";

      String texts[3];
      texts[0] = "==DS18B20==";
      texts[1] = text_temperature;;
      texts[2] = "T: " + text_kelvin +" " + text_fahrenheit;
      texts[3] = text_limit;

      Lcd.displayTextX4(texts);
    }

};
```
\newpage

## 2.3 Plik konfiguracyjnych - CONFIG.cpp

Zawiera konfigurację wszystkich pinów oraz załącza wszystkie klasy.

```cpp
// DEPENDENCES
#include "ScreenLcd.cpp"
#include "DiodeLed.cpp"
#include "MyEncoder.cpp"
#include "Button.cpp"
#include "ds18b20.cpp"

#define SERIAL_PORT 9600

// DS18B20 TEMPERATURE PIN
#define DS_PIN  4

// LCD SCREEN PIN
#define RS 12
#define E 11
#define D4 10
#define D5 9
#define D6 8
#define D7 7

// COUNTER ENCODER PIN
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define RESET_BTN_PIN 5

// LED DIODE PIN
#define LED_PIN 6

// MIN/MAX BUTTON PIN
#define BTN_PIN 13
```
\newpage

## 2.4 Wyświetlacz LCD 20x4 -  SreenLcd.cpp

```cpp
#include <LiquidCrystal.h>
#include <Arduino.h>
#define LCD_CHAR 20
#define LCD_ROWS 4
class ScreenLcd {	
	private:
		LiquidCrystal lcd;
	public:
		ScreenLcd(int rs, int en, int d4, int d5, int d6, int d7)
		: lcd(rs, en, d4, d5, d6, d7) {}
	
	void setup() {
		lcd.begin(LCD_CHAR,LCD_ROWS);
	}
	void displayText(const String line) {
	
		lcd.clear();
		lcd.setCursor(0, 1);
		lcd.print(line);
	}

	void displayTextX4(const String line[3]){
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print(line[0]);

      lcd.setCursor(0, 1);
      lcd.print(line[1]);

      lcd.setCursor(0, 2);
      lcd.print(line[2]);

      lcd.setCursor(0, 3);
      lcd.print(line[3]);
    }
  
	void test() {
		lcd.clear();
		lcd.setCursor(0, 1);
		lcd.print("test");
		delay(2000);
	}
};
```


\newpage

## 2.5 Miernik temperatury DS18B20 - ds18b20.cpp
```cpp
#include <OneWire.h>
#include <DallasTemperature.h>
class TemperatureSensorDS18B20
{
  private:
    OneWire oneWire;
    DallasTemperature sensor;

  public:
    TemperatureSensorDS18B20(int pin) : oneWire(pin), sensor(&oneWire) {}

    void setup() {
      sensor.begin();
    }

    float readTemperature() {
      sensor.requestTemperatures();
      return sensor.getTempCByIndex(0);
    }

    float readKelvin(){
      return readTemperature() + 273.15;
    }

    float readFahrenheit(){
      float c = readTemperature();
      float f = (c* 9.0 / 5.0)+32.0;
      return  f;
    }

    void test(){
        float get_temperature = readTemperature();
        String text_temperature = "T: " + String(get_temperature) + " C";
        Serial.println(text_temperature);
    }
};
```
\newpage


## 2.6 Endkoder - MyEncoder.cpp

```cpp
#include <Encoder.h>

class MyEncoder 
{
  private:
    Encoder rotary;
    int resetBtn;
    long counter;

  public:
    MyEncoder(int pinA, int pinB, int btnPin)
      : rotary(pinA, pinB), resetBtn(btnPin), counter(0) {}

    void setup() {
      pinMode(resetBtn, INPUT_PULLUP);
    }

    long getCounter()
    {
      static long lastCounter = 0;
      long currentCounter = rotary.read() >> 2;

      if (lastCounter != currentCounter) {;
        lastCounter = currentCounter;
      }
      
      if (digitalRead(resetBtn) == LOW) {
        rotary.write(0);
        lastCounter = 0;
        Serial.println(0);
        return 0;
      }
      return currentCounter;

    }

    void test()
    {
      long counter = getCounter();
      Serial.println("Count: " + String(counter));
    }
};
```
\newpage

## 2.7 Przycisk - Button.cpp

```cpp
#include <Arduino.h>
class Button 
{
  private:
      int a;
      int b;
      int pin_btn;

    public:
      Button(int pin) 
      {
        a = 0;
        b = 0;
        pin_btn = pin;
        pinMode(pin_btn, INPUT);
      }

      int detectPress() 
      {
          a = digitalRead(pin_btn);
          if (a == HIGH && b == LOW) {
            return 1;  
          }
          else return 0;

          b = a;
      }

      void test()
      {
        int option = detectPress();
        if(option==1) Serial.println("STATE: MAX+");
        if(option==0) Serial.println("STATE: MIN");

      }

      String text_limit()
      {
        int option = detectPress();
        if(option==1) return "MAX:";
        if(option==0) return "MIN:";

      }
};
```
\newpage

## 2.8 Dioda LED -  DiodeLed.cpp

```cpp
#include <Arduino.h>
class DiodeLed
{
  private:
    int ledPin;

  public:
    DiodeLed(int pin) {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);
    }

    void on(){
      digitalWrite(ledPin, HIGH);
    }

    void off(){
      digitalWrite(ledPin, LOW);
    }

    void blink() {
      on();
      delay(1000);

      off();
      delay(1000);
    }

    void limit_max(long limit, int temperature)
    {
      if(temperature >= limit) off();
      else on();
    }

    void limit_min(long limit, int temperature)
    {
      if(temperature > limit) on();
      else off();
    }

    void test()
    {
      on();
    }
};
```

\newpage



# 3. Problematyka

## 3.1 Problem układu Raspberry Pi Pico W - RP2040
Wybór Arduino Uno zamiast Rasberry PI Pico W rozwiązał problem nie działającej obsługi czunika DS18B20. 
Biblioteka 'OneWire' powodowała błędy podczas wgrywania programu na układ Pico.
Po wielu nieudanych próbach udało się znaleźć odpowiednią obługę w MicroPython, jednak reszta założeń projektu tak jak obługa ekranu LCD, była dość złożona i powodowała problemy.
Płytka Arduino Uno, lepiej współpracowało ze środowiskiem Arduino IDEE, i czas wgrywania oraz komplilacji był o wiele szybszy, co umożliwiło bardziej komfortową pracę.

Kod MicroPython do obsługi Ds18B20:

```python
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


##  3.2 OOP - Programowanie obiektowe
Dodatkowo w celu ułatwienia i utrzymania przejrzystości kodu wykorzystane zostało programowanie obiektowe i podział na klasy i obiekty w C++.


## 3.3 Podział plików
Wydzielenie różnych funkcjonalności do osobnych plików, które: 
- ułatwiają rozbudowę
- ułatwiają znalezienie błędu
- są skalowanlne, pliki można wykorzystać wielokrotnie w innym projekcie

\newpage

## 3.4 Testowanie
W głównej klasie 'MiernikTemperatury9' znajduję się metoda "Testowanie()" w której można wywołać funkcję do testowania czy podłączony element komunikuje się z Arduino. \newline
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

\newpage



