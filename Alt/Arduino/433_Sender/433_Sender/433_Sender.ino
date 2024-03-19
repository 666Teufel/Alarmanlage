#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int Button = 12;
int timer = 0;
void setup() {
  mySwitch.enableTransmit(10);  // Der Sender wird an Pin 10 angeschlossen
Serial.begin(9600);
   mySwitch.enableReceive(0);
   pinMode(Button, INPUT_PULLUP);
   pinMode(13, OUTPUT);
   }
void loop() {
   if (!digitalRead(Button)){
  mySwitch.send(910657, 24);
  delay(100);
  mySwitch.send(15011112 , 24);
  delay(5000);
  mySwitch.send(910658, 24);
  if (mySwitch.available()) // Wenn ein Code Empfangen wird...
  {
    int value = mySwitch.getReceivedValue(); // Empfangene Daten werden unter der Variable "value" gespeichert.
  
    if (value == 0) // Wenn die Empfangenen Daten "0" sind, wird "Unbekannter Code" angezeigt.
    {
      Serial.println("Unbekannter Code");
    } 
    
    else { // Wenn der Empfangene Code brauchbar ist, wird er hier an den Serial Monitor gesendet.{
    if(mySwitch.getReceivedValue() == 29876);{
              Serial.print("Empfangen: ");
              digitalWrite(13, HIGH);
              delay(1000);
              digitalWrite(13, LOW);
              }




 
    mySwitch.resetAvailable(); // Hier wird der Empfänger "resettet"
  }// Der 433mhz Sender versendet die Dezimalzahl „1234“
    // Eine Sekunde Pause, danach startet der Sketch von vorne

   }
}}  
