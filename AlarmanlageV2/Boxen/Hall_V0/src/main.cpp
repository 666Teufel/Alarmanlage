#include <Arduino.h> // hinzufügen von Arduino Bibliothek

const int Hallsensor_Pin = 34; // hinzufügen Hallsensor Pin

//  Hinzufügen von Variabeln

int analog_wert_hallsensor = 0; //  Variabel für den Wert des Analog Pin der mit dem Hall Sensor verbunden ist
int min_hall = 10000;           //  Variabel für den minmalwert des Hall Sensor Pins start mit einem hohen Wert außerhalb des Messwerte Bereichs
int max_hall = 0;               //  Variabel für den maximalwert des Hall Sensor Pins start mit niedrigen wert minimaler wert beim Messen

// Setup wird genau einmal Durchlaufen
void setup()
{
  Serial.begin(115200); //  Kommunikation Computer und Mikrocontroller geschwindigkeit
  delay(1000);          //  Kurzes warten
}
// Loop wird Dauerhaft wiederholt
void loop()
{
  delay(1);                                            //  Pause für Stabilere Werte
  analog_wert_hallsensor = analogRead(Hallsensor_Pin); //  Auslesen des Hallsensor Pins durch vergleichen mit 3.3 V und zwischenspeichern auf der Variabel analog_wert_hallsensor
  max_hall = max(max_hall, analog_wert_hallsensor);    // Vergleich welcher wert Größer ist
  min_hall = min(min_hall, analog_wert_hallsensor);    // Vergleich welcher wert kleiner ist

  Serial.print(">Aktueller_Hallsensor_Wert:"); //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(analog_wert_hallsensor);      //  Ausgeben des Wertes für Teleploter
  Serial.print(">Max_Wert_Hallsensor:");       //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(max_hall);                    //  Ausgabe Mamimalwert des Hallsensors
  Serial.print(">Min_Wert_Hallsensor:");       //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(min_hall);                    //  Ausgabe des Minimal Wertes des Hallsensors
}