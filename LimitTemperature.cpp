#include <Arduino.h>

#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define ENCODER_RESET_PIN 5

class LimitTemperature
{
private:
  int Min;
  int Max;
  int SIA;
  int SIB;
  int SI_SW;

  int a = 1;
  int b = 1;
  int t = 0;

public:


  String text_max = "0";
  String text_min = "0";

  LimitTemperature() : Min(0), Max(0), SIA(ENCODER_A_PIN), SIB(ENCODER_B_PIN), SI_SW(ENCODER_RESET_PIN)
  {
  }
  

  void setup()
  {
    pinMode(SIB, INPUT);
    pinMode(SIA, INPUT);
  }

  void setMin(int newMin) { Min = newMin; }
  void setMax(int newMax) { Max = newMax; }

  int getMin() { return Min; }
  int getMax() { return Max; }

  void setTextMax(String newtext) { text_max = newtext; }
  void setTextMin(String newtext) { text_min = newtext; }

  String getTextMax() { return text_max;}
  String getTextMin() { return text_min;}


  void testPrint(String cursor_max, String cursor_min)
  {
      Serial.println("===========");
      Serial.println("MAX: " + String(getMax()) + cursor_max);
      Serial.println("MIN: " + String(getMin()) + cursor_min);
      Serial.println("===========");
  }

  void testPrintMax() { testPrint(" <==", " "); }
  void testPrintMin() { testPrint(" ", " <=="); }


  void detect(int detect)
  {

    // LIMIT MAX
    int choose = detect;

    if (choose == 1){
        a = digitalRead(SIA);

        // reset counter
        if (digitalRead(SI_SW) == LOW) {setMax(0); testPrintMax();}

        // enkdoer
        if ((b == 1) && (a == 0) && ((millis() - t) > 50))
        {
          t = millis();
          (digitalRead(SIB) == 1) ? setMax(getMax() + 1) : setMax(getMax() - 1);
          testPrintMax();      
        }
        setTextMax("MAX: " + String(getMax()) + " C <==");
        setTextMin("MIN: " + String(getMin()) + " C");


    }


    // LIMIT MIN
    if (choose == 0)
    {

      // reset counter
      if (digitalRead(SI_SW) == LOW) { setMin(0); testPrintMin(); }

      // enkdoer
      a = digitalRead(SIA);
      if ((b == 1) && (a == 0) && ((millis() - t) > 50))
      {
        t = millis();
        (digitalRead(SIB) == 1) ? setMin(getMin() + 1) : setMin(getMin() - 1);
        testPrintMin();
      }

      setTextMax("MAX: " + String(getMax()) + " C");
      setTextMin("MIN: " + String(getMin()) + " C <==");
    }
  }


};
