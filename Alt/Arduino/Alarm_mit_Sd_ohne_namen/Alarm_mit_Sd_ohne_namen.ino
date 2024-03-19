#include <SPI.h>      
#include <MFRC522.h>  
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include "RTClib.h"

#include "Sodaq_wdt.h"
#ifdef ARDUINO_ARCH_AVR
#define DIAG_STREAM Serial
#elif ARDUINO_ARCH_SAMD
#define DIAG_STREAM SerialUSB
#endif

File myFile;
#define RST_PIN     5
#define SS_PIN      53 

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN); 

const int chipSelect = 10;
String dataString = "An";
//byte Henry_uid[] = {0xA0, 0xC1, 0xF2, 0x32};
byte Henry_uid[] = {0x27, 0xFC, 0x1A, 0xB5};
byte Barbara_uid[] = {0xF9, 0xA5, 0x36, 0xC1};
byte Andy_uid[] = {0x07, 0x49, 0x1E, 0xB5};
byte Nilse_uid[] = {0x49, 0xCC, 0x50, 0xC2};
byte Ersatz2_uid[] = {0xD0, 0x11, 0x25, 0x32};
byte Ersatz1_uid[] = {0x67, 0x37, 0x1E, 0xB5};

 
int Henry_check = false;
int Barbara_check = false;
int Ersatz1_check = false;
int Ersatz2_check = false;
int Nilse_check = false;
int Andy_check = false;
int Alarm_check = false;
int Zaehler = 1;
int TimerAlarm =60; //Sekunden
int Sattelkammer =38;
int Spinn =34;
int Gruen =36;
int Hupe = 490;
int b = 0;
int Relay = 22;

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
int Laut = 0; //0 Aus 1 An
  

void setup() {
  SPI.begin();      
  mfrc522.PCD_Init();
  
 lcd.begin();
 lcd.createChar(1, a);
 lcd.home();
 lcd.noBacklight();
 lcd.clear();
 
 TimerAlarm = TimerAlarm * 1000;
 pinMode(Sattelkammer, INPUT_PULLUP);
 pinMode(Spinn, INPUT_PULLUP);
 pinMode(Gruen, INPUT_PULLUP);
 TimerAlarm = millis();
 Serial.begin(9600);
 pinMode(Hupe, OUTPUT);
 pinMode(Relay, OUTPUT);
 digitalWrite(Relay, LOW);
 delay(1000);
 lcd.backlight();
  delay(1000);
  lcd.noBacklight();
   Serial.println("Start up");
 Serial.print("Initializing SD card...");
 if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
}
  Serial.println("card initialized.");

 
if (SD.exists("AN.TXT")&&!digitalRead(Sattelkammer)&&!digitalRead(Spinn)&&!digitalRead(Gruen)) {
Serial.println("An");
 Alarm_check = true;
        }
else{
  Alarm_check = false;
  if (SD.exists("AN.TXT")){
    if(Laut == 1){
               digitalWrite(Relay, HIGH);
 delay(500);
 digitalWrite(Relay, LOW);
 }
           SD.remove("AN.TXT");
  }
  Serial.println("deaktivirt");
  lcd.print("deaktiviert");
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.noBacklight();
  lcd.clear();
 }
myFile.close();
myFile.close();
 sodaq_wdt_enable(WDT_PERIOD_4X);
}
void loop() {
    wdtrest();
  
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
        Andy_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != Andy_uid[j]) {
        Andy_check = false;
      }
    }
         Nilse_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != Nilse_uid[j]) {
        Nilse_check = false;
      }
    }
            Ersatz1_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != Ersatz1_uid[j]) {
        Ersatz1_check = false;
      }
    }

       Ersatz2_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != Ersatz2_uid[j]) {
        Ersatz2_check = false;
      }
    }
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  }


    if (Henry_check) {
         lcd.setCursor(0,0);
        lcd.print("Hallo Henry");

        Alarmabak();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
    lcd.noBacklight();
        lcd.clear();
    }
 
    if (Barbara_check) {
        lcd.setCursor(0,0);
        lcd.print("Hallo B");
        lcd.setCursor(7,0);
        lcd.write(byte(1));
        lcd.setCursor(8,0);
        lcd.print("rbel");
        lcd.setCursor(12,0);
        lcd.write(byte(0));

        Alarmabak();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
    lcd.noBacklight();
        lcd.clear();
    }
 if (Andy_check) {
        lcd.setCursor(0,0);
        lcd.print("Hallo Andy");

        Alarmabak();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
    lcd.noBacklight();
        lcd.clear();
    }
     if (Ersatz1_check) {
        lcd.setCursor(0,0);
        lcd.print("Hallo Ersatz1");
                    
Alarmabak();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
    lcd.noBacklight();
        lcd.clear();
    }
     if (Ersatz2_check) {
        lcd.setCursor(0,0);
        lcd.print("Hallo Ersatz2");

Alarmabak();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
    lcd.noBacklight();
        lcd.clear();
    }
         if (Nilse_check) {
        lcd.setCursor(0,0);
        lcd.print("Hallo Herr Niehls");

    // print to the serial port too:

Alarmabak();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
delay(2000);
wdtrest();
    lcd.noBacklight();
        lcd.clear();
    }


  
 if(digitalRead(Sattelkammer)&&Alarm_check == true){
 Serial.println("Alarm");

laut();
 }
  if(digitalRead(Spinn)&&Alarm_check == true){
Serial.println("Alarm");
                
laut();
 }
  if(digitalRead(Gruen)&&Alarm_check == true){
Serial.println("Alarm");
 
laut();
 }
 delay(100);
 }
void Alarmabak(){
  // Alarm anlage Aktiwiren/deaktiwiren
      if (Alarm_check == false){
        Alarm_check = true;
        lcd.backlight();
        lcd.setCursor(0,1);
        lcd.print("Alarm aktiviert");
       File dataFile = SD.open("An.txt", FILE_WRITE);
       if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }

         sodaq_wdt_enable(WDT_PERIOD_1DIV64);
        delay(10000);
      }

       else {
        Alarm_check = false;
        lcd.backlight();
        lcd.setCursor(0,1);
        lcd.print("Alarm deaktiviert");
        SD.remove("AN.TXT");
        delay(10000);
        
}

    }
    void laut(){
      Serial.println(Laut);
    while(Zaehler <= 90){
      if(Laut == 1){
 digitalWrite(Relay, HIGH);
  wdtrest();
 delay(500);
   wdtrest();
 digitalWrite(Relay, LOW);
 delay(500);
      }
      wdtrest();
  wdtrest();
 Serial.print(Zaehler);
 Serial.println(".Alarm");
     Zaehler++;
 wdtrest();
    }
    
     digitalWrite(Relay, LOW);
     Alarm_check = false;
     Serial.println("deaktivirt");
     Zaehler = 1;
     delay(10000);

    }
    void wdtrest(){
if (sodaq_wdt_flag) {
    sodaq_wdt_flag = false;
    sodaq_wdt_reset();
  Serial.println("WDT interrupt has been triggered");
  }
    }
