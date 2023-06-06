/*

  JAKUB ACHTELIK, KACPER OBORZYŃŚKI

  MIERNIK TEMPERATURY 9

  - Odczyt temperatury z czunika DS18B20, w
  - Wyświetalnie jej na ekranie LCD,
  - wykorzystanie endokera do ustawienia progu temperatury maksymalnej i minimalnej,
  - zapewnienie sygnalizacji przekroczenia progu.

*/

#include "lcd.cpp"
#include "ds18b20.cpp"
#include "myencoder.cpp"

#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define RESET_BTN_PIN 5
#define DS_PIN  4

#define LED 4
#define RS 12
#define E 11
#define D4 10
#define D5 9
#define D6 8
#define D7 7

MyEncoder myEncoder(ENCODER_A_PIN, ENCODER_B_PIN, RESET_BTN_PIN);
TemperatureSensor temperatureSensor(DS_PIN);
ScreenLcd lcd(RS, E, D4, D5, D6, D7);

void setup()
{

  myEncoder.setup();
  // Serial.begin(115200);
  Serial.begin(9600);

  // Serial.begin(9600);
  temperatureSensor.begin();
  lcd.setup();
  Serial.print("dupa");

}


void loop()
{

  float temperature = temperatureSensor.readTemperature();
  String rotation = "PROG: " + String(myEncoder.getCounter());

  // delay(5000);
  lcd.displayText(
    "TEMP. :" + String(temperature) + " C",
    rotation
  );
  temperatureSensor.test();
}