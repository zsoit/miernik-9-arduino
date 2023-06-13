
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
      if(temperature > limit) off();
      else on();
    }

    void limit_min(long limit, int temperature)
    {
      if(temperature > limit) off();
      else on();
    }

    void test()
    {
      on();
    }
};