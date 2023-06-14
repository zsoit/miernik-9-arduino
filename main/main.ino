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
      // Serial.println("Test - arduino is connect");
      // TemperatureSensor.test();
      // Lcd.test();
      // Btn.test();
      // Led.test();


      Limit.setTemp(TemperatureSensor.readTemperature());

      Limit.test(Btn.detectPress());

      int choose = Btn.detectPress();
      if(choose == 1) Led.limit_max(Limit.getMax(), TemperatureSensor.readTemperature());
      if(choose == 0) Led.limit_min(Limit.getMin(), TemperatureSensor.readTemperature());

      String xd[3];

      xd[1] = Limit.getTextMin();
      xd[0] = Limit.getTextMax();
      

      if(Btn.detectPress()==0) xd[2] = TemperatureSensor.text_temperature();
      else xd[2] = TemperatureSensor.text_second_row();

      // xd[3] = "simea";

      Lcd.displayTextX4(xd);     

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
      Btn(BTN_PIN)
      { 
      }


    void Main() 
    {
      
      Limit.test(Btn.detectPress());




      String texts[3];

      texts[0] = TemperatureSensor.text_temperature();
      texts[1] = TemperatureSensor.text_second_row();
      texts[2] = Limit.text_max;
      texts[3] = Limit.text_min;

      Lcd.displayTextX4(texts);

    }

};


MiernikTemperatury9 projekt;

void setup() {
  projekt.setup();
}

void loop() {
  projekt.loop();
}




