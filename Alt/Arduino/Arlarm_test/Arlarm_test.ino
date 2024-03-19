#include <SPI.h>      
#include <MFRC522.h>  
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define RST_PIN     5          
#define SS_PIN      53 

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN); 

byte Henry_uid[] = {0xA0, 0xC1, 0xF2, 0x32};
byte Barbara_uid[] = {0xF9, 0xA5, 0x36, 0xC1};

int Henry_check = false;
int Barbara_check = false;
int Alarm_check = false;

int Laser1 = 8;
int Laser2 = 9;
int Laserstaerke1 = 255;
int Laserstaerke2 = 0;
int RGBGruen = 23;
int RGBRot = 22;

byte Smiley[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte a[] = {
  B01010,
  B00000,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
  B00000
};


void setup() {
 pinMode(Laser1, OUTPUT);
 pinMode(Laser2, OUTPUT);
 pinMode(RGBGruen, OUTPUT);
 pinMode(RGBRot, OUTPUT);
   
  SPI.begin();      
  mfrc522.PCD_Init();
  lcd.begin();
     lcd.createChar(0, Smiley);
      lcd.home();
           lcd.createChar(1, a);
      lcd.home();
          lcd.noBacklight();
        lcd.clear();
        analogWrite(Laser1, 0);
        analogWrite(Laser2, 0);  
}






void loop() {

  
  // put your main code here, to run repeatedly:
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
    Serial.print("Gelesene UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // Abstand zwischen HEX-Zahlen und führende Null bei Byte < 16
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      
    }
        Henry_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != Henry_uid[j]) {
        Henry_check = false;
      }
    }
 
    // UID Vergleichen mit red_uid
    Barbara_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != Barbara_uid[j]) {
        Barbara_check = false;
      }
    }
 
    if (Henry_check) {
      lcd.backlight();
      lcd.print("Hallo Henry");
      lcd.setCursor(12,0);
      lcd.write(byte(0));
      if (Alarm_check == false){
        Alarm_check = true;
        lcd.setCursor(0,1);
        lcd.print("Alarm aktiviert");
        analogWrite(Laser1, Laserstaerke1);
        analogWrite(Laser2, Laserstaerke2);
      }

       else {
                Alarm_check = false;
        lcd.setCursor(0,1);
        lcd.print("Alarm deaktiviert");
        analogWrite(Laser1, 0);
        analogWrite(Laser2, 0);
 }
    delay(10000);
    lcd.noBacklight();
        lcd.clear();
    }
 
    if (Barbara_check) {
  lcd.backlight();
  lcd.print("Hallo B");
lcd.setCursor(7,0);
lcd.write(byte(1));
lcd.setCursor(8,0);
lcd.print("rbel");
lcd.setCursor(13,0);
lcd.write(byte(0));
 if (Alarm_check = false){
 
 }
    delay(10000);
    lcd.noBacklight();
        lcd.clear();

    }
 
    // Versetzt die gelesene Karte in einen Ruhemodus, um nach anderen Karten suchen zu können.


  }
 
} 
