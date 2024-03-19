#include "Sodaq_wdt.h"

#ifdef ARDUINO_ARCH_AVR

#define DIAG_STREAM Serial

#elif ARDUINO_ARCH_SAMD

#define DIAG_STREAM SerialUSB

#endif

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int Fenster =9;
int fenster =6;
int Tur =4;
void setup() {
  // put your setup code here, to run once:

pinMode(fenster , INPUT_PULLUP);
pinMode(Fenster , INPUT_PULLUP);
pinMode(Tur , INPUT_PULLUP);
mySwitch.enableTransmit(3);
Serial.begin(9600);
sodaq_wdt_enable(WDT_PERIOD_1X);
}

void loop() {
  wdtrest();
  // put your main code here, to run repeatedly:
if(digitalRead(Tur)){  mySwitch.send(15011112 , 24);
Serial.println(1);
}
if(digitalRead(fenster)){
  mySwitch.send(15011112 , 24);
  Serial.println(2);
}
//if(digitalRead(Fenster)){
  //mySwitch.send(15011112 , 24);
//}
delay(100);
}
    void wdtrest(){
if (sodaq_wdt_flag) {
    sodaq_wdt_flag = false;
    sodaq_wdt_reset();
  Serial.println("WDT interrupt has been triggered");
  }
    }
