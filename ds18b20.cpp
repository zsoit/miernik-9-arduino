#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor 
{
  private:
    OneWire oneWire;
    DallasTemperature sensor;

  public:
    TemperatureSensor(int pin) : oneWire(pin), sensor(&oneWire) {}

    void begin() {
      // Serial.begin(115200);
      // delay(2);
      sensor.begin();
      // delay(20);
    }

    float readTemperature() {
      sensor.requestTemperatures();
      return sensor.getTempCByIndex(0);
    }

    void test()
    {
      Serial.println("test hello");
    }
};
