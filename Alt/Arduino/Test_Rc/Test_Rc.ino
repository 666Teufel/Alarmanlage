#include "RCSwitch.h" // (1)

 RCSwitch Sendemodul = RCSwitch(); // (2)

 void setup() {
 Sendemodul.enableTransmit(2); // (3)
 }
 void loop() { 
  Sendemodul.send(analogRead(0)+1, 16); // (4)
 delay(10);
 }
