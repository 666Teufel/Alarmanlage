#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar[] = {
  B00000,
  B00000,
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000
};

void setup() {
  lcd.begin();
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.write(0);
}

void loop() { }
