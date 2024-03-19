#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#include "Sodaq_wdt.h"
#ifdef ARDUINO_ARCH_AVR
#define DIAG_STREAM Serial
#elif ARDUINO_ARCH_SAMD
#define DIAG_STREAM SerialUSB
#endif


int Laser_Pin = 10;
int Laserstr = 255;
int Lichtsensoren_A;
int Lichtsensoren_B;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Laser_Pin, OUTPUT);
mySwitch.enableTransmit(2);
 sodaq_wdt_enable(WDT_PERIOD_4X);
}

void loop() {
  // put your main code here, to run repeatedly:
wdtrest();
analogWrite(Laser_Pin, Laserstr);
Lichtsensoren_A = analogRead(A0);
Lichtsensoren_B = analogRead(A1);
if(Lichtsensoren_B <= 900 && Lichtsensoren_A <= 900 &&Lichtsensoren_B >= 960 && Lichtsensoren_A >= 960) {
//mySwitch.send((Lichtsensoren_A), 16);
//mySwitch.send(("17239826"), 16);
//mySwitch.send((Lichtsensoren_B), 16);
Serial.println(Lichtsensoren_A);
Serial.println(Lichtsensoren_B);
Serial.println("Alarm");
delay(1000);
}
delay(100);
Serial.println(Lichtsensoren_A);
Serial.println(Lichtsensoren_B);
}
    void wdtrest(){
if (sodaq_wdt_flag) {
    sodaq_wdt_flag = false;
    sodaq_wdt_reset();
  Serial.println("WDT interrupt has been triggered");
  }
    }
