#include <Arduino.h>


class Button 
{
  private:
      int a;
      int b;
      int pin_btn;
      int pressBtn;
      

    public:
      Button(int pin) 
      {
        a = 0;
        b = 0;
        pressBtn = 0;
        pin_btn = pin;
        pinMode(pin_btn, INPUT);
        
      }

      void setB(int bset){
        b = bset;
      }

      int getB()
      {
        return b;
      }


      int detectPress()
      {
        a = digitalRead(pin_btn);
        if (a == HIGH && b == LOW) {
            return 1;
        }
        else{
             return 0;
        }
      }

      void test()
      {
        int option = detectPress();
        if(option==1) Serial.println("STATE: MAX+");
        if(option==0) Serial.println("STATE: MIN");

      }

      String text_limit()
      {
        int option = detectPress();
        if(option==1) return "MAX:";
        if(option==0) return "MIN:";
      }
};