#include <Arduino.h> // hinzufügen von Arduino Bibliothek
#include <FastLED.h>
// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN 5 // Werte eintragen
// Define the array of leds
CRGB leds[NUM_LEDS];

#include <esp32_can.h> // hinzufügen von esp32_can Bibliothek

void printFrame(CAN_FRAME *message)
{
  Serial.print(message->id, HEX);
  if (message->extended)
    Serial.print(" X ");
  else
    Serial.print(" S ");
  Serial.print(message->length, DEC);
  for (int i = 0; i < message->length; i++)
  {
    Serial.print(message->data.byte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void gotHundred(CAN_FRAME *frame)
{
  Serial.print("Got special frame!  ");
  printFrame(frame);
}

#include <Adafruit_ADS1X15.h> // hinzufügen von Adafruit_ADS1X15 Bibliothek
#include <Wire.h>
#define I2C_SDA 8
#define I2C_SCL 9
Adafruit_ADS1115 ads;           /* Use this for the 16-bit version */
#define ADS1115I2C_ADDRESS 0x48 // I2C Adresse des ADS1115

//  Hinzufügen von Variabeln
int16_t adc0, adc1, adc2, adc3; //  Variabeln für die Messwerte des ADS1115
//  Variabel für den Wert des Analog Pin der mit dem Hall Sensor verbunden ist
int min_hall[4] = {100000, 100000, 100000, 100000}; //  Variabel für den minmalwert des Hall Sensor Pins start mit einem hohen Wert außerhalb des Messwerte Bereichs
int max_hall[4];                                    //  Variabel für den maximalwert des Hall Sensor Pins start mit niedrigen wert minimaler wert beim Messen

const int messungen_anzahl = 10;
int hallsensor_werte[messungen_anzahl][4]; //  Array für die Messwerte des Hall Sensor Pins
int position_im_array1 = 0;                //  Variabel für die Position des aktuellen Messwertes im Array
int position_im_array2[4] = {0, 0, 0, 0};  //  Variabel für die Position des aktuellen Messwertes im Array
int gesamt_hall[4];                        //  Variabel für denn Wert aller Messwerte des Hall Sensor Pins addirt
int durchnittswert_hall[4];                //  Variabel für den durchschnittswert aller Messwerte des Hall Sensor

void setup()
{

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200); //  Starten der Serial Port
  delay(10000);         //  Wartezeit für das Starten der Serial Port
  Serial.println("Initializing ...");
  CAN0.setCANPins(GPIO_NUM_44, GPIO_NUM_43);
  CAN0.begin(1000000);

  Serial.println("Ready ...!");
  CAN_FRAME txFrame;
  txFrame.rtr = 0;
  txFrame.id = 0x123;
  txFrame.extended = false;
  txFrame.length = 4;
  txFrame.data.int8[0] = 0x12;
  txFrame.data.int8[1] = 0x1A;
  txFrame.data.int8[2] = 0xFF;
  txFrame.data.int8[3] = 0x5D;

  Serial.println();
  CAN0.sendFrame(txFrame);
  Serial.println("sendFrame");
  //CAN0.watchFor(0x100, 0xF00);     // setup a special filter
  Serial.println("watchFor");
  //CAN0.watchFor();                 // then let everything else through anyway
  Serial.println("watchFor");
  CAN0.setCallback(0, gotHundred); // callback on that first special filter
  Serial.println("setCallback");
  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
    while (1)
      ;
  }

  //  Schleife zum befüllen der Array mit den Messwerte des Hall Sensor Pins
  for (position_im_array1 = 0; position_im_array1 < 4; position_im_array1++)
  {
    for (position_im_array2[position_im_array1] = 0; position_im_array2[position_im_array1] < messungen_anzahl; position_im_array2[position_im_array1]++)
    {
      hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1] = ads.readADC_SingleEnded(position_im_array1);
      gesamt_hall[position_im_array1] = gesamt_hall[position_im_array1] + hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1];
    }
  }
  leds[0] = CRGB(0, 0, 255);
  FastLED.show();
}

void loop()
{
  byte i = 0;
  CAN_FRAME message;
  for (position_im_array1 = 0; position_im_array1 < 4; position_im_array1++)
  {
    gesamt_hall[position_im_array1] = gesamt_hall[position_im_array1] - hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1]; //  Subtraktion des Messwertes der gleich überschriebenen Position aus denn gesamten Messwerte des Arrays

    hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1] = ads.readADC_SingleEnded(position_im_array1);
    ; //  Aktualisierung des aktuellen Messwertes des Hall Sensor Pins

    // Serial.print(">An_hall_value:");                                                              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
    // Serial.println(hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1]); //  Für Teleploter Ausgabe des aktuellen Messwertes des Hall Sensor Pins

    max_hall[position_im_array1] = max(max_hall[position_im_array1], hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1]); //  Aktualisierung des maximalen Messwertes des Hall Sensor Pins
    min_hall[position_im_array1] = min(min_hall[position_im_array1], hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1]); //  Aktualisierung des minimalen Messwertes des Hall Sensor Pins

    gesamt_hall[position_im_array1] = gesamt_hall[position_im_array1] + hallsensor_werte[position_im_array2[position_im_array1]][position_im_array1]; // additieren des aktuellen Messwertes des Hall Sensor Pins zu den gesamten Messwertes im Array

    position_im_array2[position_im_array1] = position_im_array2[position_im_array1] + 1; // Position im Array um 1 erhöhen

    //  Wenn die Position im Array größer ist als die anzahl der messungen durchlaeufe, wird die Position im Array auf 0 gesetzt
    if (position_im_array2[position_im_array1] >= messungen_anzahl)
    {
      position_im_array2[position_im_array1] = 0;
    }
    durchnittswert_hall[position_im_array1] = gesamt_hall[position_im_array1] / messungen_anzahl;

    // Serial.print(">Smooth1:");                            //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
    // Serial.println(durchnittswert_hall[position_im_array1]);                 //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
    // Serial.print(">Aktueller_Hallsensor_Wert:");         //  Für Telleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
    // Serial.println(hallsensor_werte[position_im_array]); //  Ausgeben des Wertes für Teleploter
    // Serial.print(">Max_Wert_Hallsensor:");               //  Für Telleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
    // Serial.println(max_hall);                            //  Ausgabe Mamimalwert des Hallsensors
    // Serial.print(">Min_Wert_Hallsensor:");               //  Für Telleploter kennzeichnung das dieser Wert als Diagram dargestellt werden soll(Auf dem angeschlossenden PC)
    // Serial.println(min_hall);                            //  Ausgabe des Minimal Wertes des Hallsensors
  }
  /*Serial.print(">Smooth0:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[0]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth1:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[1]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth2:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[2]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth3:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[3]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
*/
  delay(10); //  WartezeiT

  if (CAN0.read(message))
  {

    printFrame(&message);
    Serial.println("read");
    Serial.println(CAN0.read(message));
    // Send out a return message for each one received
    // Simply increment message id and data bytes to show proper transmission
    // Note: this will double the traffic on the network (provided it passes the filter above)
    message.id++;
    for (i = 0; i < message.length; i++)
    {
      message.data.uint8[i]++;
    }
    CAN0.sendFrame(message);
  }
  // or, just plain send traffic periodically


  message.id++;
  message.length = 8;
  for (i = 0; i < message.length; i++)
  {
    message.data.uint8[i]= 0xFF;
  }
  CAN0.sendFrame(message);
 Serial.println(Can0.available());
  if (durchnittswert_hall[0] > 19000 && durchnittswert_hall[1] > 19000)
  {
    leds[0] = CRGB(0, 10, 0);
  }
  else if (durchnittswert_hall[0] < 19000 or durchnittswert_hall[1] < 19000)
  {
    leds[0] = CRGB(25, 0, 0);
  }

  FastLED.show();

  delay(100);
}