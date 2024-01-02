#include <Arduino.h> // hinzufügen von Arduino Bibliothek

const int Hallsensor_Pin = 34; // hinzufügen Hallsensor Pin

//  Hinzufügen von Variabeln

//  Variabel für den Wert des Analog Pin der mit dem Hall Sensor verbunden ist
int min_hall = 10000; //  Variabel für den minmalwert des Hall Sensor Pins start mit einem hohen Wert außerhalb des Messwerte Bereichs
int max_hall = 0;     //  Variabel für den maximalwert des Hall Sensor Pins start mit niedrigen wert minimaler wert beim Messen

const int messungen_anzahl = 10;
int hallsensor_werte[messungen_anzahl]; //  Array für die Messwerte des Hall Sensor Pins
int position_im_array = 0;              //  Variabel für die Position des aktuellen Messwertes im Array
int gesamt_hall = 0;                    //  Variabel für denn Wert aller Messwerte des Hall Sensor Pins addirt
int durchnittswert_hall = 0;            //  Variabel für den durchschnittswert aller Messwerte des Hall Sensor

void setup()
{
  Serial.begin(115200); //  Starten der Serial Port
  delay(1000);          //  Wartezeit für das Starten der Serial Port

  //  Schleife zum befüllen der Array mit den Messwerte des Hall Sensor Pins
  for (int schleifen_durchlaeufe = 0; schleifen_durchlaeufe < messungen_anzahl; schleifen_durchlaeufe++)
  {
    hallsensor_werte[schleifen_durchlaeufe] = analogRead(Hallsensor_Pin);
    gesamt_hall = gesamt_hall + hallsensor_werte[schleifen_durchlaeufe];
  }
}

void loop()
{
  gesamt_hall = gesamt_hall - hallsensor_werte[position_im_array]; //  Subtraktion des Messwertes der gleich überschriebenen Position aus denn gesamten Messwerte des Arrays

  hallsensor_werte[position_im_array] = analogRead(Hallsensor_Pin); //  Aktualisierung des aktuellen Messwertes des Hall Sensor Pins

  Serial.print(">An_hall_value:");                     //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(hallsensor_werte[position_im_array]); //  Für Teleploter Ausgabe des aktuellen Messwertes des Hall Sensor Pins

  max_hall = max(max_hall, hallsensor_werte[position_im_array]); //  Aktualisierung des maximalen Messwertes des Hall Sensor Pins
  min_hall = min(min_hall, hallsensor_werte[position_im_array]); //  Aktualisierung des minimalen Messwertes des Hall Sensor Pins

  gesamt_hall = gesamt_hall + hallsensor_werte[position_im_array]; // additieren des aktuellen Messwertes des Hall Sensor Pins zu den gesamten Messwertes im Array

  position_im_array = position_im_array + 1; // Position im Array um 1 erhöhen

  //  Wenn die Position im Array größer ist als die anzahl der messungen durchlaeufe, wird die Position im Array auf 0 gesetzt
  if (position_im_array >= messungen_anzahl)
  {
    position_im_array = 0;
  }
  durchnittswert_hall = gesamt_hall / messungen_anzahl;

  Serial.print(">Smooth:");                            //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall);                 //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Aktueller_Hallsensor_Wert:");         //  Für Telleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(hallsensor_werte[position_im_array]); //  Ausgeben des Wertes für Teleploter
  Serial.print(">Max_Wert_Hallsensor:");               //  Für Telleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(max_hall);                            //  Ausgabe Mamimalwert des Hallsensors
  Serial.print(">Min_Wert_Hallsensor:");               //  Für Telleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
  Serial.println(min_hall);                            //  Ausgabe des Minimal Wertes des Hallsensors
}