// LCD DISPLAY 16X1
#include <LiquidCrystal.h>
#include <Arduino.h>

#define LCD_CHAR 20
#define LCD_ROWS 4

class ScreenLcd
{
  private:
    LiquidCrystal lcd;

  public:
    ScreenLcd(int rs, int en, int d4, int d5, int d6, int d7)
      : lcd(rs, en, d4, d5, d6, d7){}

    void setup() {
      lcd.begin(LCD_CHAR, LCD_ROWS);
    }

    void displayText(const String line) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(line);
    }

    void displayTextLcd(const String line[2]){
      lcd.clear();
      
      lcd.setCursor(0, 0);
      lcd.print(line[0]);
      
      lcd.setCursor(0, 1);
      lcd.print(line[1]);
      
      lcd.setCursor(0, 2);
      lcd.print(line[2]);
    }


    void test() {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("test");
      delay(2000);
    }
};
