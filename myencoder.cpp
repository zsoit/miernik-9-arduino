#include <Encoder.h>

class MyEncoder {
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
};
