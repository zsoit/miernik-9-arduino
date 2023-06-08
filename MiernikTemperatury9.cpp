#include "CONFIG.cpp"

class MiernikTemperatury9 
{
  private:
    MyEncoder MyEncoder;
    TemperatureSensorDS18B20 TemperatureSensor;
    ScreenLcd Lcd;
    DiodeLed Led;
    Button Btn;

  public:
    void Testowanie()
    {
      // Serial.println("Test - arduino is connect");
      // TemperatureSensor.test();
      // Lcd.test();
      // MyEncoder.test();
      // Btn.test();
      // Led.test();
    }

    void loop() 
    {
      Wyswietlacz();
      SygnalizcajaProgu();
      Testowanie();
    }

    void setup() 
    {
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
      Btn(BTN_PIN) {}


    void SygnalizcajaProgu() 
    {
      // SYGNALIZACJA PROGU  
      long limit = MyEncoder.getCounter();
      float limit_temperature = TemperatureSensor.readTemperature();
      limit_temperature = static_cast<int>(limit_temperature);

      int option = Btn.detectPress();
      if (option == 1)
        Led.limit_max(3, limit_temperature);
      if (option == 0)
        Led.limit_min(3, limit_temperature);
    }

    void Wyswietlacz() 
    {
      // ODCZYT TEMPERATURY
      float get_temperature = TemperatureSensor.readTemperature();
      long get_counter = MyEncoder.getCounter();

      // NAPISY
      String text_limit_header = Btn.text_limit();
      String text_limit = text_limit_header + String(get_counter) + " C";
      String text_temperature = "T:" + String(get_temperature);

      String text = text_temperature + " " + text_limit;

      // WYSWIETLENIE NA EKRANIE
      Lcd.displayText(text);
    }

};

