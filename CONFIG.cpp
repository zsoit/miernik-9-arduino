// DEPENDENCES
#include "ScreenLcd.cpp"
#include "DiodeLed.cpp"
#include "LimitTemperature.cpp"
#include "Button.cpp"
#include "ds18b20.cpp"

#define SERIAL_PORT 9600

// DS18B20 TEMPERATURE PIN
#define DS_PIN  13

// LCD SCREEN PIN
#define RS 12
#define E 11
#define D4 10
#define D5 9
#define D6 8
#define D7 7

// COUNTER ENCODER PIN
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define ENCODER_RESET_PIN 5

// LED DIODE PIN
#define LED_PIN 6

// MIN/MAX BUTTON PIN
#define BTN_PIN 4
