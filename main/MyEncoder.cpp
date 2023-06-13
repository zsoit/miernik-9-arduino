#include <Encoder.h>

class MyEncoder 
{
  private:
    Encoder rotary;
    int resetBtn;
    long counter;
    long lastCounter;

  public:
    MyEncoder(int pinA, int pinB, int btnPin)
      : rotary(pinA, pinB), resetBtn(btnPin), counter(0) {
        lastCounter = 0;
      }

    void setup() {
      pinMode(resetBtn, INPUT_PULLUP);
    }

     long getCounter()
  {
    long currentCounter = rotary.read() >> 2;

    if (lastCounter != currentCounter)
    {
      lastCounter = currentCounter;
    }

    if (digitalRead(resetBtn) == LOW) {
      resetCounter();
    }

    return currentCounter;
  }

  void resetCounter()
  {
    rotary.write(0);
    lastCounter = 0;
  }

    long getCounterTwo()
    {
      getCounter();
    }


    void test()
    {
      long counter = getCounter();
      Serial.println("Count: " + String(counter));
    }

};
