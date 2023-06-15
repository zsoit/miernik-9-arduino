#include <Arduino.h>
class Button 
{
private:
  int pin;
  int buttonState;
  int prevButtonState;
  unsigned long lastDebounceTime;
  bool isButtonOn;

public:
  Button(int pin) : pin(pin), buttonState(HIGH), prevButtonState(HIGH), lastDebounceTime(0), isButtonOn(false) {
    pinMode(pin, INPUT);
  }

  void update() {
    int reading = digitalRead(pin);

    if (reading != prevButtonState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > 50) {
      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState == LOW) {
          isButtonOn = !isButtonOn;

          if (isButtonOn) {
            Serial.println("Button: MAX");
          } else {
            Serial.println("Button: MIN");
          }
        }
      }
    }

    prevButtonState = reading;
  }

  bool isOn() {
    return isButtonOn;
  }

  int detectPress()
  {
    update();
    if(isOn()) { return 1; }
    else { return 0;}
  }

  void test(){
    int choose = detectPress();
    if(choose==1) Serial.println("on");
    if(choose==0) Serial.println("off");

  }
};