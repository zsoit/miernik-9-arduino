/*

  JAKUB ACHTELIK, KACPER OBORZYŃŚKI

  MIERNIK TEMPERATURY 9

  - 1. Odczyt temperatury z czunika DS18B20, w
  - 2. Wyświetalnie jej na ekranie LCD,
  - 3. wykorzystanie endokera do ustawienia progu temperatury maksymalnej i minimalnej,
  - 4. zapewnienie sygnalizacji przekroczenia progu.

*/

#include "ScreenLcd.cpp"
#include "DiodeLed.cpp"
#include "MyEncoder.cpp"
#include "Button.cpp"

#include "ds18b20.cpp"

#include "CONFIG.cpp"

MyEncoder myEncoder(ENCODER_A_PIN, ENCODER_B_PIN, RESET_BTN_PIN);
TemperatureSensor TemperatureSensor(DS_PIN);
ScreenLcd Lcd(RS, E, D4, D5, D6, D7);
DiodeLed led(LED_PIN);
Button btn(BTN_PIN);

void setup()
{
  Serial.begin(SERIAL_PORT);
  myEncoder.setup();
  TemperatureSensor.setup();
  Lcd.setup();
}



void SygnalizcajaProgu()
{

  // SYGNALIZACJA PROGU  
  long limit = myEncoder.getCounter();
  float limit_temperature = TemperatureSensor.readTemperature();
  limit_temperature = static_cast<int>(limit_temperature);

  int option = btn.detectPress();
  if(option==1) led.limit_max(3,limit_temperature);;
  if(option==0)  led.limit_min(3,limit_temperature);;

 
}



void Wyswietlacz()

{
  // ODCZYT TEMPERATURY
  float get_temperature = TemperatureSensor.readTemperature();
  long get_counter = myEncoder.getCounter();

  // NAPISY
  String text_limit_header = btn.text_limit();
  String text_limit = text_limit_header + String(get_counter) + " C";
  String text_temperature = "T: " + String(get_temperature) + " C";
  
  // WYSWIETLENIE NA EKRANIE
  Lcd.displayText(text_temperature, text_limit);

}

void TestujPomiar()
{
  float get_temperature = TemperatureSensor.readTemperature();
  String text_temperature = "T: " + String(get_temperature) + " C";
  Serial.println(text_temperature);
}

void loop()
{

  Wyswietlacz();
  SygnalizcajaProgu();
  // TestujPomiar();


}



