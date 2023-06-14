#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

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
      return f;
    }

    String text_temperature() {return "T:" + String(readTemperature()) + " C"; }
    String text_kelvin() { return String(readKelvin()) + "K"; }
    String text_fahrenheit() { return  String(readFahrenheit() ) + "F"; }
    String text_second_row() { return "T: " + text_kelvin() +" " + text_fahrenheit(); }

    void test(){
        float get_temperature = readTemperature();
        String text_temperature = "T: " + String(get_temperature) + " C";
        Serial.println(text_temperature);
    }
};