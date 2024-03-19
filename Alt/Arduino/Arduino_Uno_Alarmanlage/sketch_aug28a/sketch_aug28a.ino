#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include "RTClib.h"
//#include <RCSwitch.h>
//RCSwitch mySwitch = RCSwitch();
int readbyte;
int address = 0;
byte value;

File myFile;
#define RST_PIN     9
#define SS_PIN      10

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int chipSelect = 6;
const int Reset_pin = 8;
const int Relay = 2;

byte Laut = 1; //0 Aus 1 An
int Abwarten = 500;//Wartezeit vor Alarm
int nummer;
//Reset
unsigned long Zeit;
unsigned long Reset_timer = 10800000;
//unsigned long Reset_timer = 10000;


int Tuehren_Werte;
int minimal = 1023;


String dataString = "An";

const byte Admin_uid[] = {0xA0, 0xC1, 0xF2, 0x32};
const byte Henry_uid[] = {0x27, 0xFC, 0x1A, 0xB5};
const byte Barbara_uid[] = {0xF9, 0xA5, 0x36, 0xC1};
const byte Andy_uid[] = {0x07, 0x49, 0x1E, 0xB5};
const byte Nilse_uid[] ={0x49, 0xCC, 0x50, 0xC2};
const byte Ersatz2_uid[] = {0xD0, 0x11, 0x25, 0x32};
const byte Ersatz1_uid[] = {0x67, 0x37, 0x1E, 0xB5};

bool Admin_check = false;
bool Henry_check = false;
bool Barbara_check = false;
bool Ersatz1_check = false;
bool Ersatz2_check = false;
bool Nilse_check = false;
bool Andy_check = false;
bool Alarm_check = false;

bool Sattelkammer = false;
bool Spinn = false;
bool Gruen = false;

int Zaehler = 1;
int TimerAlarm = 60; //Sekunden

int menu = 1;

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
/*InPut_Output*/ 
  Serial.begin(115200);
Serial.println("An");
/*Chip*/ 
  SPI.begin();
  mfrc522.PCD_Init();
  // mySwitch.enableReceive(37);

/*Lcd*/ 
  lcd.begin();
  lcd.createChar(1, a);
  lcd.home();
  lcd.noBacklight();
  lcd.clear();
pinMode(Sattelkammer, INPUT_PULLUP);
  pinMode(Spinn, INPUT_PULLUP);
  pinMode(Gruen, INPUT_PULLUP);
  delay(100);
  //Serial.println(analogRead(Sattelkammer));
  //Serial.println(analogRead(Spinn));

  pinMode(Reset_pin, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);

  if (!SD.begin(chipSelect) && EEPROM.read(2) == 0) {
    lcd.clear();
    lcd.backlight();
    lcd.println("SdCard n.i.o.   ");
      digitalWrite(Relay, HIGH);
      delay(150);
      digitalWrite(Relay, LOW);
    
    //Serial.println("Card failed or not present");
    // don't do anything more:
    delay(10000);
    lcd.clear();
    lcd.noBacklight();
  }
  
 int Schleife = 0; 
 value = EEPROM.read(address);
   Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.print(value);
  Serial.println();
  
while (Schleife < 10000 && minimal > 980 && EEPROM.read(2) == 0 && value == 1) {
  Schleife++;
  Serial.println("");
Tuehren_Werte = analogRead(A2);
minimal = 10000;
if (Tuehren_Werte<minimal){
  minimal = Tuehren_Werte;
}
Serial.print(minimal);
}

 //Serial.println("card initialized");


  if (value == 1 && minimal > 980) {
    //Serial.println("An");
    Alarm_check = true;
    EEPROM.write(2, 1); //Überprüfung bestanden
  }
  else {
    EEPROM.write(2, 0); // Überprüfung nicht Bestanden
    Alarm_check = false;
    if (value == 1) {
      if (Laut == 1) {
        digitalWrite(Relay, HIGH);
        delay(500);
        digitalWrite(Relay, LOW);
      }

      File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
      if (Aktiv) {
        Aktiv.println("Fehler eine geöffnete Tür");
        Aktiv.close();
        // print to the serial port too:
      }
      SD.remove("AN.TXT");
       EEPROM.write(0, 0);

    
    //Serial.println("deaktivirt");
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
  }
  lcd.noBacklight();
  lcd.clear();
}
void loop() {
  
  Zeit = millis();
  Resetcheck();
  wache();
  Tuehren_Werte = analogRead(A2);
  Serial.println(Tuehren_Werte);
if(Serial.available()) {
  while(Serial.available() > 0) {
    Serial.print(Serial.available());
  Reset();
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();   
  }
}

 KartenCheck();

  // Versetzt die gelesene Karte in einen Ruhemodus, um nach anderen Karten suchen zu können.

    if (Sattelkammer == true && Alarm_check == true) {
      Serial.println("Sattelkammer");
      File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
      if (Aktiv) {
        Aktiv.println("Sattelkammer");
        Aktiv.close();
        // print to the serial port too:
      }
      laut();
    }
  
  
  
    if (Spinn == true && Alarm_check == true) {
      Serial.println("Spinnt");
      File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
      if (Aktiv) {
        Aktiv.println("Spinnt");
        Aktiv.close();
        // print to the serial port too:
      }
      laut();
    
  }

    if (Gruen == true && Alarm_check == true) {

      Serial.println("Gruene");
      File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
      if (Aktiv) {
        Aktiv.println("Gruene");
        Aktiv.close();
        // print to the serial port too:
      }
      laut();
    }


}

void Alarmabak() {
  // Alarm anlage Aktivieren/deaktivieren
  if (Alarm_check == false) {
    Alarm_check = true;
    EEPROM.write(0, 1);// An
    EEPROM.write(2, 0); // Überprüfung nicht Bestanden
    lcd.backlight();
    lcd.setCursor(0, 1);
    lcd.print("Alarm aktiviert");
    File dataFile = SD.open("An.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    File Aktiv = SD.open("AKTIV.TXT", FILE_WRITE);
    if (Aktiv) {
      Aktiv.println(": Aktiv");
      Aktiv.close();
    }
    delay(5000);
    Reset();
  }

  else {
    Alarm_check = false;
    EEPROM.write(0, 0); // Aus
    EEPROM.write(2, 0); // Überprüfung nicht Bestanden
    lcd.backlight();
    lcd.setCursor(0, 1);
    lcd.print("Alarm deaktiviert");
    SD.remove("AN.TXT");
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.println(": Deaktivirt");
      Aktiv.close();
      // print to the serial port too:
    }
    delay(5000);
    Reset();
  }

}
void laut() {
  Serial.println(Laut);
  while (Zaehler <= 90) {
    if (Laut == 1) {
      digitalWrite(Relay, HIGH);
      delay(500);
      KartenCheck();
      digitalWrite(Relay, LOW);
      delay(500);
      KartenCheck();
    }
    Serial.print(Zaehler);
    Serial.println(".Alarm");
    Zaehler++;
    
}
  digitalWrite(Relay, LOW);
 
  Reset();
}
void Resetcheck() {
  if (Zeit > Reset_timer) {
    File Timer = SD.open("Timer.txt", FILE_WRITE);
    if (Timer) {
      Zeit = millis();
      Timer.print(" + ");
      Timer.print(Zeit);
      Timer.close();
      // print to the serial port too:
    }

    digitalWrite(Reset_pin, HIGH);
  }
}
void Reset() {

  File Timer = SD.open("Timer.txt", FILE_WRITE);
  if (Timer) {
    Zeit = millis();
    Timer.print(" + ");
    Timer.print(Zeit);
    Timer.close();
    // print to the serial port too:
  }
  digitalWrite(Reset_pin, HIGH);
}
void wache() {
Tuehren_Werte = analogRead(A2);
}

void KartenCheck() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
    Serial.print("Gelesene UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // Abstand zwischen HEX-Zahlen und führende Null bei Byte < 16
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);

    }


    Henry_check = true;
    for (int j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != Henry_uid[j]) {
        Henry_check = false;
      }
    }

    // UID Vergleichen mit red_uid
    Barbara_check = true;
    for (int j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != Barbara_uid[j]) {
        Barbara_check = false;
      }
    }
    Andy_check = true;
    for (int j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != Andy_uid[j]) {
        Andy_check = false;
      }
    }
    Nilse_check = true;
    for (int j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != Nilse_uid[j]) {
        Nilse_check = false;
      }
    }
    Ersatz1_check = true;
    for (int j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != Ersatz1_uid[j]) {
        Ersatz1_check = false;
      }
    }

    Ersatz2_check = true;
    for (int j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != Ersatz2_uid[j]) {
        Ersatz2_check = false;
      }
    }

    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
  }
  if (Henry_check) {
    lcd.setCursor(0, 0);
    lcd.print("Hallo Henry");
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.print("Henry");

      Aktiv.close();
      // print to the serial port too:
    }
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();
  }
  if (Barbara_check) {
    lcd.setCursor(0, 0);
    lcd.print("Hallo B");
    lcd.setCursor(7, 0);
    lcd.write(byte(1));
    lcd.setCursor(8, 0);
    lcd.print("rbel");
    lcd.setCursor(12, 0);
    lcd.write(byte(0));
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.print("Barbara");
      Aktiv.close();
      // print to the serial port too:
    }
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();
  }
  if (Andy_check) {
    lcd.setCursor(0, 0);
    lcd.print("Hallo Andy");
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.print("Andy");
      Aktiv.close();
      // print to the serial port too:
    }
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();
  }
  if (Ersatz1_check) {
    lcd.setCursor(0, 0);
    lcd.print("Hallo Ersatz1");
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.print("Ersatz1");
      Aktiv.close();
      // print to the serial port too:
    }
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();
  }
  if (Ersatz2_check) {
    lcd.setCursor(0, 0);
    lcd.print("Hallo Ersatz2");
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.print("Ersatz2");
      Aktiv.close();
      // print to the serial port too:
    }
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();
  }
  if (Nilse_check) {
    lcd.setCursor(0, 0);
    lcd.print("Hallo Herr Niehls");
    File Aktiv = SD.open("Aktiv.txt", FILE_WRITE);
    if (Aktiv) {
      Aktiv.print("Herr Niehls");
      Aktiv.close();
      // print to the serial port too:
    }
    Alarmabak();
    lcd.noBacklight();
    lcd.clear();
  }
}
