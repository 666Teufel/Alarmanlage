/* Sketch for Tutorial 14
Author: Maximilian Hentsch
Sketch zu Arduino Tutorial 14 - Displaymenü
https://www.youtube.com/watch?v=DuAG98P9Seo
*/
long a = 0;
int sensorWert = 0;
int Ledr = 6;
int Ledg = 3;
int Ledb = 9;
int Ledrz = 0;
int Ledgz = 0;
int Ledbz = 255;
int r = 0;
int pr = 0;
int g = 0;
int pg = 0;
int b = 0;
int pb = 0;
int Starke = 0;
long Pause = 3600000;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int Test = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
// 2 und 12 Tauschen
int upButton = 4;
int downButton = 2;
int selectButton = 7;
int Zuruck = 8;
int menu = 1;
int an = 1;
void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  
  updateMenu();
  
}

void loop() {
  sensorWert = analogRead(A0);
  if (sensorWert == 0){
    Starke = 127;
  }
  else {
     Starke = 255;
  }
   if( Test == 0) {
  if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}
else {
   if (!digitalRead(downButton)){
    an++;
    aan();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    an--;
    aan();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeZeit();
    aan();
    delay(100);
    while (!digitalRead(selectButton));
}
}}
void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Rot");
      lcd.setCursor(0, 1);
      lcd.print(" Gruen");
      break;
    case 2:
      lcd.clear();
      lcd.print(">Gruen");
      lcd.setCursor(0, 1);
      lcd.print(" Blau");
      break;
    case 3:
      lcd.clear();
      lcd.print(">Blau");
      lcd.setCursor(0, 1);
      lcd.print(" Zufall");
      break;
          case 4:
      lcd.clear();
      lcd.print(">Zufall");
      lcd.setCursor(0, 1);
      lcd.print(" Anzeit");
      break;
    case 5:
      lcd.clear();
      lcd.print(">Anzeit");
      break;
    case 6:
      menu = 5;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
       case 5:
      action5();
      break;
  }
}

void action1() {
  lcd.clear();
  lcd.print(">Rot");
    delay(1500);
    lcd.noBacklight();
    analogWrite(Ledr, Starke);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, 0);
    delay(Pause);
    analogWrite(Ledr, 0);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, 0);
  delay(1500);
    lcd.clear();
     lcd.backlight();
}
void action2() {
  lcd.clear();
  lcd.print(">Gruen");
    delay(1500);
    lcd.noBacklight();
      analogWrite(Ledr, 0);
    analogWrite(Ledg, Starke);
    analogWrite(Ledb, 0);
    delay(Pause);
    analogWrite(Ledr, 0);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, 0);
  delay(1500);
    lcd.clear();
     lcd.backlight();
}
void action3() {
  lcd.clear();
  lcd.print(">Blau");
      delay(1500);
    lcd.noBacklight();
      analogWrite(Ledr, 0);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, Starke);
    delay(Pause);
    analogWrite(Ledr, 0);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, 0);
  delay(1500);
    lcd.clear();
      lcd.backlight();
}
void action4() {
  lcd.clear();
  lcd.print(">Zufall");
  delay(1500);
  lcd.noBacklight();
  while(a < 3600000){
    a++;
    r = Ledrz - 1;
pr = Ledrz + 5;
r = Ledrz - 5;
pg = Ledrz + 5;
g = Ledrz - 5;
pb = Ledbz + 5;
Ledrz = random(r,pr) / 255;
Ledgz = random(g,pg) / 255;
Ledbz = random(b,pb) / 255;
                analogWrite(Ledr, r);
    analogWrite(Ledg, g);
    analogWrite(Ledb, b);
  }
      analogWrite(Ledr, 0);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, 0);
    a = 0;
}
void action5() {
  lcd.clear();
  Test = 1;
  delay(1500);
}
void aan() {
  switch (an) {
    case 0:
      an = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">15min");
      lcd.setCursor(0, 1);
      lcd.print(" 30min");
      break;
    case 2:
      lcd.clear();
      lcd.print(">30min");
      lcd.setCursor(0, 1);
      lcd.print(" 45min");
      break;
    case 3:
      lcd.clear();
      lcd.print(">45min");
      lcd.setCursor(0, 1);
      lcd.print(" 60min");
      break;
          case 4:
      lcd.clear();
      lcd.print(">60min");
      lcd.setCursor(0, 1);
      lcd.print(" Zurueck");
      break;
                case 5:
      lcd.clear();
      lcd.print(">Zurueck");
      break;
    case 6:
      an = 5;
      break;
  }
}

void executeZeit() {
  switch (an) {
    case 1:
      p();
      break;
    case 2:
      e();
      break;
    case 3:
      d();
      break;
    case 4:
      f();
      break;
          case 5:
      z();
      break;
  }
}

void p() {
  lcd.clear();
  lcd.print(">15min");
Pause = 900000;
  delay(1500);
    lcd.clear();
}
void e() {
  lcd.clear();
  lcd.print(">30min");
Pause = 1800000;
  delay(1500);
    lcd.clear();
}
void d() {
  lcd.clear();
  lcd.print(">45min");
Pause = 2700000;
  delay(1500);
    lcd.clear();
}
void f() {
  lcd.clear();
  lcd.print(">60min");
  Pause = 3600000;
  delay(1500);
}
void z() {
  lcd.clear();
  Test = 0;
  menu = 1;
  delay(1500);
}
