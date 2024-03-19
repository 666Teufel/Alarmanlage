#include <Arduino.h> // hinzufügen von Arduino Bibliothek
#include <FastLED.h>
// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN 5 // Werte eintragen
// Define the array of leds
CRGB leds[NUM_LEDS];

// ————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
#ifndef ARDUINO_ARCH_ESP32
#error "Select an ESP32 board"
#endif
#include <ACAN_ESP32.h>
static const uint32_t DESIRED_BIT_RATE = 1000UL * 1000UL; // 1 Mb/s
long gBlinkLedDate = 0;
static uint16_t gPhase1 = 0;
static uint32_t gPhase2 = 0;

static const uint16_t HIGHEST_STANDARD_IDENTIFIER = (1 << 11) - 1;
static const uint32_t HIGHEST_EXTENDED_IDENTIFIER = (1 << 29) - 1;

// ————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
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

  //  Initialisierung des ADS1115
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

  // Initialisierung des CAN Bus
  Serial.println("Configure ESP32 CAN");
  ACAN_ESP32_Settings settings(DESIRED_BIT_RATE);
  settings.mRequestedCANMode = ACAN_ESP32_Settings::LoopBackMode;
  settings.mRxPin = GPIO_NUM_44; // Optional, default Rx pin is GPIO_NUM_4
  settings.mTxPin = GPIO_NUM_43; // Optional, default Tx pin is GPIO_NUM_5
  const ACAN_ESP32_Filter filter = ACAN_ESP32_Filter::acceptStandardFrames();
  const uint32_t errorCode = ACAN_ESP32::can.begin(settings, filter);
  if (errorCode == 0)
  {
    Serial.print("Bit Rate prescaler: ");
    Serial.println(settings.mBitRatePrescaler);
    Serial.print("Time Segment 1:     ");
    Serial.println(settings.mTimeSegment1);
    Serial.print("Time Segment 2:     ");
    Serial.println(settings.mTimeSegment2);
    Serial.print("RJW:                ");
    Serial.println(settings.mRJW);
    Serial.print("Triple Sampling:    ");
    Serial.println(settings.mTripleSampling ? "yes" : "no");
    Serial.print("Actual bit rate:    ");
    Serial.print(settings.actualBitRate());
    Serial.println(" bit/s");
    Serial.print("Exact bit rate ?    ");
    Serial.println(settings.exactBitRate() ? "yes" : "no");
    Serial.print("Sample point:       ");
    Serial.print(settings.samplePointFromBitStart());
    Serial.println("%");
    Serial.println("Configuration OK!");
  }
  else
  {
    Serial.print("Configuration error 0x");
    Serial.println(errorCode, HEX);
  }
}

//----------------------------------------------------------------------------------------

void loop()
{
  //  Schleife zum befüllen der Array mit den Messwerte des Hall Sensor Pins
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

  //  Wenn der Durchschnittswert des Hall Sensor Pins größer als 19000 ist, wird die LED Rot
  if (durchnittswert_hall[0] > 19000 or durchnittswert_hall[1] > 19000)
  {
    leds[0] = CRGB(255, 0, 0);
  }
  else if (durchnittswert_hall[0] < 19000 && durchnittswert_hall[1] < 19000)
  {
    leds[0] = CRGB(0, 25, 0);
  }

  FastLED.show();

  if (gBlinkLedDate < millis())
  {
    gBlinkLedDate = millis();
    Serial.print("At ");
    Serial.print(gBlinkLedDate / (60 * 1000));
    Serial.print(" min, sending state: phase1 0x");
    Serial.print(gPhase1, HEX);
    Serial.print(", phase2 0x");
    Serial.println(gPhase2, HEX);
  }
  //--- Send standard frame
  CANMessage frame;
  if (gPhase1 <= (HIGHEST_STANDARD_IDENTIFIER * 2 + 1))
  {
    frame.id = gPhase1 >> 1;
    frame.rtr = (gPhase1 & 1) != 0;
    if (ACAN_ESP32::can.tryToSend(frame))
    {
      gPhase1 += 1;
      Serial.print("**** Sent standard frame, id 0x");
    }
  }
  else if (gPhase2 <= (HIGHEST_EXTENDED_IDENTIFIER * 2 + 1))
  {
    frame.ext = true;
    frame.id = gPhase2 >> 1;
    frame.rtr = (gPhase2 & 1) != 0;
    if (ACAN_ESP32::can.tryToSend(frame))
    {
      gPhase2 += 1;
    }
  }
  //--- Received frame ?
  if (ACAN_ESP32::can.receive(frame))
  {
    Serial.print("**** Received ");
    Serial.print(frame.ext ? "extended " : "standard ");
    Serial.print(frame.rtr ? "remote " : "data ");
    Serial.print("frame, id 0x");
    Serial.println(frame.id, HEX);
  }
  delay(450);
}