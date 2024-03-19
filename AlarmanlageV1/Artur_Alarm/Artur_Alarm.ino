#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
unsigned long timersenden;
unsigned long timerAlarmzk;
boolean Alarm = false;
int Safe = 17035839;
int Ausloesen = 17039826;
int Boxen = 11;
int LaserPin = 12;
int LaserStaerke = 125;
int Lichtsensor1 = 0;
int Lichtsensor2 = 0;
int Lichtsensorausloesemin = 855;
int Lichtsensorausloesemax = 970;

void setup() {
  // put your setup code here, to run once:
pinMode(LaserPin, OUTPUT);
pinMode(Boxen, INPUT_PULLUP);
timersenden = millis();
timerAlarmzk = millis();
mySwitch.enableTransmit(10);
analogWrite(LaserPin, LaserStaerke);
}

void loop() {
  // put your main code here, to run repeatedly:
if ((millis() - timersenden) >= 7000) {
  if( Alarm == false ){
    mySwitch.send(Safe , 24);
  }
  else{
  mySwitch.send(Ausloesen , 24);
 }
 timersenden = millis();

if ((millis() - timerAlarmzk) >= 20000) {
  if( Alarm == true) {
    Alarm = false;
  }
  timerAlarmzk = millis();
}
}
Lichtsensor1 = analogRead(A0);
Lichtsensor2 = analogRead(A1);
if( Lichtsensor1 < Lichtsensorausloesemin || Lichtsensor1 > Lichtsensorausloesemax) {
  if( Lichtsensor2 < Lichtsensorausloesemin || Lichtsensor2 > Lichtsensorausloesemax) {
     Alarm = true;
  }
}
if (digitalRead(Boxen)){
  Alarm = true;
}
}
