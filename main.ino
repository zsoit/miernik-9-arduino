#include "MiernikTemperatury9.cpp"

/*

  Autorzy: JAKUB ACHTELIK, KACPER OBORZYŃŚKI
  LABOLATORIUM SYSTEMOW ELEKTRONICZNYCH
  Temat: MIERNIK TEMPERATURY 9

  - 1. Odczyt temperatury z czunika DS18B20, w
  - 2. Wyświetalnie jej na ekranie LCD,
  - 3. wykorzystanie endokera do ustawienia progu temperatury maksymalnej i minimalnej,
  - 4. zapewnienie sygnalizacji przekroczenia progu.

*/


MiernikTemperatury9 projekt;

void setup() {
  projekt.setup();
}

void loop() {
  projekt.loop();
}


