#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

class TemperatureSensorDS18B20
{
  private:
    OneWire oneWire;
    DallasTemperature sensor;
    unsigned long lastReadTime;  // Czas ostatniego odczytu temperatury
    unsigned long readInterval;  // Interwał czasowy pomiędzy odczytami

  public:
    TemperatureSensorDS18B20(int pin, unsigned long interval = 1000) : oneWire(pin), sensor(&oneWire), lastReadTime(0), readInterval(interval) {}

    void setup() {
      sensor.begin();
    }

    float readTemperature() {
      unsigned long currentTime = millis();
      
      // Sprawdzamy, czy wystarczył czas od ostatniego odczytu
      if (currentTime - lastReadTime >= readInterval) {
        sensor.requestTemperatures();
        lastReadTime = currentTime;
      }
      
      return sensor.getTempCByIndex(0);
    }

    float readKelvin() {
      return readTemperature() + 273.15;
    }
    
    float readFahrenheit() {
      float c = readTemperature();
      float f = (c * 9.0 / 5.0) + 32.0;
      return f;
    }

    String text_temperature() { return "T:" + String(readTemperature()) + " C"; }
    String text_kelvin() { return String(readKelvin()) + "K"; }
    String text_fahrenheit() { return String(readFahrenheit()) + "F"; }
    String text_second_row() { return "T: " + text_kelvin() + " " + text_fahrenheit(); }

    void test() {
        float get_temperature = readTemperature();
        String text_temperature = "T: " + String(get_temperature) + " C";
        Serial.println(text_temperature);
    }
};
