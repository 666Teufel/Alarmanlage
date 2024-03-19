#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

boolean Alarm = false;
unsigned long timersenden;
unsigned long timerAlarmzk;
int Safe1 = 17035839;
int Ausloesen1 = 17039826;
int Safe2 = 26395839;
int Ausloesen2 = 26399826;
int LaserPin = 12;
int LaserStaerke = 125;
int Lichtsensor1 = 0;
int Lichtsensor2 = 0;
int Lichtsensorausloesemin = 855;
int Lichtsensorausloesemax = 970;
int value = mySwitch.getReceivedValue();

void setup() {
  // put your setup code here, to run once:
pinMode(LaserPin, OUTPUT);
timersenden = millis();
timerAlarmzk = millis();
mySwitch.enableTransmit(10);
mySwitch.enableReceive(0);
analogWrite(LaserPin, LaserStaerke);
}

void loop() {
  // put your main code here, to run repeatedly:
if ((millis() - timersenden) >= 5000) {
    if( Alarm == false ){
    mySwitch.send(Safe2 , 24);
    }
    else{
      if (mySwitch.available()) {
        if (value == Ausloesen1) {
          mySwitch.send(Ausloesen1 , 24);
          mySwitch.resetAvailable();
        }
      }
      mySwitch.send(Ausloesen2 , 24);
      mySwitch.resetAvailable();
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
}
     if (mySwitch.available()) {
        if (value == Ausloesen1) {
          Alarm = true;
          mySwitch.resetAvailable();
        }
      }
           if (mySwitch.available()) {
        if (value == Safe1) {
          Alarm = false;
          mySwitch.resetAvailable();
        }
      }
}
