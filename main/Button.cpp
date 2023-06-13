#include <Arduino.h>


class Button 
{
  private:
      int a;
      int b;
      int buttonPin;
      int pressBtn;
        bool lastState;

      
      

    public:
      Button(int pin) 
      {
        a = 0;
        b = 0;
        pressBtn = 0;
        buttonPin = pin;
        // pinMode(pin_btn, INPUT);
            // buttonPin = pin;
    lastState = HIGH;
    pinMode(buttonPin, INPUT_PULLUP);
        
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
        bool buttonState = digitalRead(buttonPin);

        if (buttonState == LOW)
        {
          // Przycisk zaciśnięty
          return 0;
        }
        else
        {
          // Przycisk niezaciśnięty
          return 1;
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