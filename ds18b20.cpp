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

    void test(){
        float get_temperature = readTemperature();
        String text_temperature = "T: " + String(get_temperature) + " C";
        Serial.println(text_temperature);
    }
};