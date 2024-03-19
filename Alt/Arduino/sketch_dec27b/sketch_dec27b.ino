 #include "RCSwitch.h"

 RCSwitch Empfangsmodul = RCSwitch(); // (1)

 void setup()
 {
 Serial.begin(9600); // (2)
 Empfangsmodul.enableReceive(0); // (3)
 pinMode(9, OUTPUT);
 }

 void loop() {
 if (Empfangsmodul.available()) // (4)
 {
 int Empfangswert = Empfangsmodul.getReceivedValue()-1; // (5)
 Serial.print("Empfangswert: ");
 Serial.println(Empfangswert);
 analogWrite(9, Empfangswert/4); // (6)
 }
 Empfangsmodul.resetAvailable(); // (7)
 }
