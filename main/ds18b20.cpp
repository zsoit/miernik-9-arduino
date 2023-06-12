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
      return f;
    }

    void test(){
        float get_temperature = readTemperature();
        String text_temperature = "T: " + String(get_temperature) + " C";
        Serial.println(text_temperature);
    }
};