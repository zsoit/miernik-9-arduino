#include "CONFIG.cpp"



class LimitTemperature
{
private:
  int Min;
  int Max;
  int SIA;
  int SIB;
  Button Btn;

  int a = 1;
  int b = 1;
  int t = 0;

public:
  LimitTemperature(int detectPress) : Min(0), Max(0), SIA(2), SIB(3), Btn(4) {
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

  void EncoderUsing()
  {

    int choose = Btn.detectPress();

    if (choose == 1)
    {
      a = digitalRead(SIA);
      if ((b == 1) && (a == 0) && ((millis() - t) > 50))
      {
        t = millis();
        if (digitalRead(SIB) == 1)
        {
          setMax(getMax() + 1);
          Serial.println("MAX: " + String(getMax()));
        }
        else
        {
          setMax(getMax() - 1);
          Serial.println("MAX: " + String(getMax()));
        }
      }
    }

    if (choose == 0)
    {
      a = digitalRead(SIA);
      if ((b == 1) && (a == 0) && ((millis() - t) > 50))
      {
        t = millis();
        if (digitalRead(SIB) == 1)
        {
          setMin(getMin() + 1);
          Serial.println("MIN: " + String(getMin()));
        }
        else
        {
          setMin(getMin() - 1);
          Serial.println("MIN: " + String(getMin()));
        }
      }
    }
  }
};

class MiernikTemperatury9 
{
  private:
    TemperatureSensorDS18B20 TemperatureSensor;
    ScreenLcd Lcd;
    DiodeLed Led;
    Button Btn;
    LimitTemperature Limit;
    int DetectPress = Btn.detectPress();


  public:
    void Testing()
    {
      // Serial.println("Test - arduino is connect");
      // TemperatureSensor.test();
      // Lcd.test();
      // MyEncoder.test();
      // Btn.test();
      // Led.test();
      Limit.EncoderUsing();

    } 

    void loop() 
    {
      // Main();
      Testing();
    }

    void setup() 
    {
      Serial.begin(SERIAL_PORT);
      TemperatureSensor.setup();
      Lcd.setup();

    }


    MiernikTemperatury9() : 
      TemperatureSensor(DS_PIN),
      Lcd(RS, E, D4, D5, D6, D7),
      Led(LED_PIN),
      Btn(BTN_PIN),
      Limit(Btn.detectPress()) { 
      }


    void Main() 
    {

      // ODCZYT TEMPERATURY
      float get_temperature = TemperatureSensor.readTemperature();
      float get_kelvin = TemperatureSensor.readKelvin();
      float get_fahrenheit = TemperatureSensor.readFahrenheit();
      
      // enkoder

      
      int limit_temperature = static_cast<int>(get_temperature);

      String limit_cursor_max;
      String limit_cursor_min;


      // przycisk
      int detect = Btn.detectPress();

      if(detect==0)
      {
          // Limit.setMin(get_counter);
          limit_cursor_max = " ";
          limit_cursor_min = "<=";
          Led.limit_min(limit_temperature,Limit.getMin());    
      }

      if(detect==1)
      {
        // Limit.setMax(get_counter);
        limit_cursor_max = "<=";
        limit_cursor_min = " ";
        Led.limit_max(limit_temperature,Limit.getMax());        

      }


      int get_limit_max = Limit.getMax();
      int get_limit_min = Limit.getMin();


      // NAPISY
      String text_limit_max = "  MAX: "  + String(get_limit_max) + " C ";
      String text_limit_min = "  MIN: " +  String(get_limit_min) + " C ";

      String text_temperature = "T:" + String(get_temperature) + " C";
      String text_kelvin = String(get_kelvin) + "K";
      String text_fahrenheit = String(get_fahrenheit ) + "F";

      String texts[3];

      texts[0] = text_temperature ;
      texts[1] = "T: " + text_kelvin +" " + text_fahrenheit;
      texts[2] = text_limit_max + limit_cursor_max;
      texts[3] = text_limit_min + limit_cursor_min;

      Lcd.displayTextX4(texts);
    }

};

