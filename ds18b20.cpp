#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor 
{
  private:
    OneWire oneWire;
    DallasTemperature sensor;

  public:
    TemperatureSensor(int pin) : oneWire(pin), sensor(&oneWire) {}

    void setup() {
      sensor.begin();
    }

    float readTemperature() {
      sensor.requestTemperatures();
      return sensor.getTempCByIndex(0);
    }
};