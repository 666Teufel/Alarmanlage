#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int Fenster =12;
int fenster =10;
int Tur =8;
void setup() {
  // put your setup code here, to run once:

pinMode(fenster , INPUT_PULLUP);
pinMode(Fenster , INPUT_PULLUP);
pinMode(Tur , INPUT_PULLUP);
mySwitch.enableTransmit(3);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(Tur)){
  mySwitch.send(15011112 , 24);
}
if(digitalRead(fenster)){
  mySwitch.send(15011112 , 24);
}
if(digitalRead(Fenster)){
  mySwitch.send(15011112 , 24);
}
}
