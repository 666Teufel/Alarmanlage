#include <RCSwitch.h>
int LED=11;
RCSwitch mySwitch = RCSwitch();

void setup() 
{
  Serial.begin(9600);
  mySwitch.enableReceive(3);  // Empfänger ist an Interrupt-Pin "0" - Das ist am UNO der Pin2
  pinMode(LED, OUTPUT); //Der Pin mit der LED (Pin13) ist jetzt ein Ausgang.
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
    {
      Serial.print("Empfangen: ");
      Serial.println( value );
        if (value == 5678)   //Verarbeitung: Wenn der Arduino die Zahl "5678" empfängt, dann... 
        {   //Programmabschnitt des IF-Befehls öffnen.
        digitalWrite(LED, HIGH); //dann soll die LED leuchten
        delay (500);   //und zwar für 0,5 Sekunden (500 Millisekunden).
        digitalWrite(LED, LOW); //danach soll die LED aus sein.
        }   //Programmabschnitt des IF-Befehls schließen.   
    }
    mySwitch.resetAvailable(); // Hier wird der Empfänger "resettet"
  }
  }
