#include "CONFIG.cpp"

class MiernikTemperatury9 
{
private:
  TemperatureSensorDS18B20 TemperatureSensor;
  ScreenLcd Lcd;
  DiodeLed Led;
  Button Btn;
  LimitTemperature Limit;
  float Temperatura;
  float previousTemperatura;
  bool readTemperatureFlag = true;

public:
  void setTemperatura(float newT) { Temperatura = newT; }
  float getTemperatura() { return Temperatura; }
  
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
    int choose = Btn.detectPress();

    String text[3];
    Limit.detect(Btn.detectPress());
    text[1] = Limit.getTextMin();
    text[0] = Limit.getTextMax();

    if (digitalRead(ENCODER_A_PIN) == LOW) {
      readTemperatureFlag = true;
      setTemperatura(TemperatureSensor.readTemperature());
      text[2] = getTemperatura();

      if (choose == 1) Led.limit_info(Limit.getMax(), text[2].toInt());
      if (choose == 0) Led.limit_info(Limit.getMin(), text[2].toInt());


    } else {
      readTemperatureFlag = false;
      Testing();
      text[2] = previousTemperatura;

      if (choose == 1) Led.limit_info(Limit.getMax(), text[2].toInt());
      if (choose == 0) Led.limit_info(Limit.getMin(), text[2].toInt());
    
    }

    Lcd.displayTextLcd(text);

    if (readTemperatureFlag) {
      previousTemperatura = Temperatura;
    }


  }
};

MiernikTemperatury9 projekt;

void setup() {
  projekt.setup();
}

void loop() {
  projekt.loop();
}
