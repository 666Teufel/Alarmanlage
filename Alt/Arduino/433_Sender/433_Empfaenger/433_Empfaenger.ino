#include <RCSwitch.h>
#include <Wire.h> // Wire Bibliothek einbinden
RCSwitch mySwitch = RCSwitch();

void setup() 
{
  Serial.begin(9600);
   mySwitch.enableReceive(0);  // Empfänger ist an Interrupt-Pin "0" - Das ist am UNO der Pin2
  mySwitch.enableTransmit(10); 
//lcd.init(); //Im Setup wird der LCD gestartet 
//lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus).

}
void loop() {
  if (mySwitch.available()) // Wenn ein Code Empfangen wird...
  {
    int value = mySwitch.getReceivedValue(); // Empfangene Daten werden unter der Variable "value" gespeichert.
  
    if (value == 0) // Wenn die Empfangenen Daten "0" sind, wird "Unbekannter Code" angezeigt.
    {
      Serial.println("Unbekannter Code");
    } 
    
    else // Wenn der Empfangene Code brauchbar ist, wird er hier an den Serial Monitor gesendet.
                  {Serial.print("Empfangen: ");
                  Serial.println(mySwitch.getReceivedValue());
    if(mySwitch.getReceivedValue() == 29876);{
              Serial.print("Empfangen: ");
              digitalWrite(13, HIGH);
              digitalWrite(13, LOW);
              Serial.println(mySwitch.getReceivedValue());
    }
{ 



} 
    mySwitch.resetAvailable(); // Hier wird der Empfänger "resettet"
  }
}}
