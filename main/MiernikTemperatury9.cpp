#include "CONFIG.cpp"


class LimitTemperature
{
  private:
    int Min;
    int Max;


  public:
    LimitTemperature(){
      Min=0;
      Max=0;
    }

    void setMin(int newMin){ Min = newMin;}
    void setMax(int newMax){ Max = newMax;}
    
    int getMin(){ return Min; }
    int getMax(){ return Max; }
};

class MiernikTemperatury9 
{
  private:
    MyEncoder MyEncoder;
    TemperatureSensorDS18B20 TemperatureSensor;
    ScreenLcd Lcd;
    DiodeLed Led;
    Button Btn;
    LimitTemperature Limit;


  public:
    void Testing()
    {
      // Serial.println("Test - arduino is connect");
      // TemperatureSensor.test();
      // Lcd.test();
      // MyEncoder.test();
      Btn.test();
      // Led.test();
    } 

    void loop() 
    {
      Main();
      Testing();
    }

    void setup() 
    {
      int now = 0;
      Serial.begin(SERIAL_PORT);
      MyEncoder.setup();
      TemperatureSensor.setup();
      Lcd.setup();
    }


    MiernikTemperatury9() : 
      MyEncoder(ENCODER_A_PIN, ENCODER_B_PIN, RESET_BTN_PIN),
      TemperatureSensor(DS_PIN),
      Lcd(RS, E, D4, D5, D6, D7),
      Led(LED_PIN),
      Btn(BTN_PIN) { }


    void Main() 
    {

      // ODCZYT TEMPERATURY
      float get_temperature = TemperatureSensor.readTemperature();
      float get_kelvin = TemperatureSensor.readKelvin();
      float get_fahrenheit = TemperatureSensor.readFahrenheit();
      
      // enkoder
      long get_counter = MyEncoder.getCounter();
      int limit_temperature = static_cast<int>(get_counter);


      String limit_cursor_max;
      String limit_cursor_min;

      // przycisk
      int detect = Btn.detectPress();
      if(detect==0)
      {

         Limit.setMax(get_counter);

        limit_cursor_max = "<=";
        limit_cursor_min = " ";        
      }

      if(detect==1)
      {

        Limit.setMin(get_counter);
        
        limit_cursor_max = " ";
        limit_cursor_min = "<=";
      }

      int get_limit_max = Limit.getMax();
      int get_limit_min = Limit.getMin();


      // NAPISY
      String text_limit_max = "MAX: "  + String(get_limit_max) + " C ";
      String text_limit_min = "MIN: " +  String(get_limit_min) + " C ";
      int STAN = Btn.detectPress();

      String text_temperature = "T:" + String(get_temperature) + " C";
      String text_kelvin = String(get_kelvin) + "K";
      String text_fahrenheit = String(get_fahrenheit ) + "F";

      String texts[3];

      texts[0] = text_temperature;
      texts[1] = "T: " + text_kelvin +" " + text_fahrenheit;
      texts[2] = text_limit_max + limit_cursor_max;
      texts[3] = text_limit_min + limit_cursor_min;

      Lcd.displayTextX4(texts);
    }

    void displayLimit()
    {
        // SYGNALIZACJA PROGU  
        long limit = MyEncoder.getCounter();
        float limit_temperature = TemperatureSensor.readTemperature();
        limit_temperature = static_cast<int>(limit_temperature);
    }

};

