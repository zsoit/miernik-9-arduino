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
      Limit.test(Btn.detectPress());

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




