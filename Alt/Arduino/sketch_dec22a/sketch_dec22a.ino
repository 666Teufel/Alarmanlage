#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
byte Arduino1[] = {
  B00000,
  B00001,
  B00010,
  B00100,
  B00101,
  B00100,
  B00010,
  B00001
};
byte Arduino2[] = {
  B00000,
  B11000,
  B00100,
  B00010,
  B11001,
  B00010,
  B00100,
  B11000
};
byte Arduino3[] = {
  B00000,
  B00011,
  B00100,
  B01001,
  B10011,
  B01001,
  B00100,
  B00011
};
byte Arduino4[] = {
  B00000,
  B10000,
  B01000,
  B00100,
  B10100,
  B00100,
  B01000,
  B10000
};
void setup()
{

  lcd.begin();
   lcd.createChar(0, Arduino1);
   lcd.createChar(1, Arduino2);
   lcd.createChar(2, Arduino3);
   lcd.createChar(3, Arduino4);
      lcd.home();
}

void loop()
{
  lcd.backlight();
lcd.setCursor(0,0);
lcd.write(byte(0));
lcd.setCursor(1,0);
lcd.write(byte(1));
lcd.setCursor(2,0);
lcd.write(byte(2));
lcd.setCursor(3,0);
lcd.write(byte(3));

}
