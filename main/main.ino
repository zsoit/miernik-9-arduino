#include "CONFIG.cpp"


class MiernikTemperatury9 
{
  private:
    TemperatureSensorDS18B20 TemperatureSensor;
    ScreenLcd Lcd;
    DiodeLed Led;
    Button Btn;
    LimitTemperature Limit;

  public:
    void Testing()
    {
      Limit.detect(Btn.detectPress());
      // Serial.println("Test - arduino is connect");
      // TemperatureSensor.test();
      // Lcd.test();
      // Btn.test();
      // Led.test();
    } 

    void loop() 
    {
      Main();
      // Testing();
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
      Btn(BTN_PIN)
      { 
      }


    void Main() 
    {
      
      Limit.detect(Btn.detectPress());

      String text[2];
      text[1] = Limit.getTextMin();
      text[0] = Limit.getTextMax();
      if(Btn.detectPress()==0) text[2] = TemperatureSensor.text_temperature() + " " +  TemperatureSensor.text_kelvin();
      else text[2] = TemperatureSensor.text_temperature() + " " + TemperatureSensor.text_fahrenheit();
      Lcd.displayTextLcd(text);    

      // LIMIT INFO
      int choose = Btn.detectPress();
      if(choose == 1) Led.limit_info(Limit.getMax(), TemperatureSensor.readTemperature());
      if(choose == 0) Led.limit_info(Limit.getMin(), TemperatureSensor.readTemperature());

    }
};


MiernikTemperatury9 projekt;

void setup() {
  projekt.setup();
}

void loop() {
  projekt.loop();
}




