#include <Arduino.h>

class Button 
{
  private:
      int a;
      int b;
      int pin_btn;

    public:
      Button(int pin) 
      {
        a = 0;
        b = 0;
        pin_btn = pin;
        pinMode(pin_btn, INPUT);
      }

      int detectPress() 
      {
          a = digitalRead(pin_btn);
          if (a == HIGH && b == LOW) {
            return 1;  
          }
          else return 0;

          b = a;
      }

      void testOption()
      {
        int option = detectPress();
        if(option==1) Serial.println("STAN: MAX+");
        if(option==0) Serial.println("STAN: MIN");

      }

      String text_limit()
      {
        int option = detectPress();
        if(option==1) return "+MAX: ";
        if(option==0) return "-MIN: ";

      }
};
