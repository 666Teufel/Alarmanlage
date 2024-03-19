#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
void setup() {
  mySwitch.enableTransmit(2);  // Der Sender wird an Pin 10 angeschlossen
}
void loop() {
  mySwitch.send(1000, 16);
    mySwitch.send(1000, 16);
      mySwitch.send(1000, 16);// Der 433mhz Sender versendet die Dezimalzahl „1234“
  delay(5000);  // Eine Sekunde Pause, danach startet der Sketch von vorne
  mySwitch.send(1, 16);
   mySwitch.send(1, 16);
    mySwitch.send(1, 16);
  delay(5000);
}  
