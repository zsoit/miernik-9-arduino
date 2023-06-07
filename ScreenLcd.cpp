#include <LiquidCrystal.h>

class ScreenLcd
{
  private:
    LiquidCrystal lcd;
    
  public:
    ScreenLcd(int rs, int en, int d4, int d5, int d6, int d7)
      : lcd(rs, en, d4, d5, d6, d7) {}


    void setup() {
          lcd.begin(20, 4);
    }

    void displayText(const String line1, const String line2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(line1);
      lcd.setCursor(0, 1);
      lcd.print(line2);
  }
};
