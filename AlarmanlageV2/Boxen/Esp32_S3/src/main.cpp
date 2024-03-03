#include <Arduino.h> // hinzufügen von Arduino Bibliothek
#include <FastLED.h>
// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN 5 // Werte eintragen
// Define the array of leds
CRGB leds[NUM_LEDS];

#include <ESP32CAN.h>         // hinzufügen von ESP32CAN Bibliothek
#include <CAN_config.h>       // hinzufügen von CAN_config Bibliothek
CAN_device_t CAN_cfg;         // CAN Config
const int rx_queue_size = 10; // Receive Queue size

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
  CAN_cfg.speed = CAN_SPEED_1000KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_43;
  CAN_cfg.rx_pin_id = GPIO_NUM_44;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  ESP32Can.CANInit();
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
  CAN_frame_t rx_frame;

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
  Serial.print(">Smooth0:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[0]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth1:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[1]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth2:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[2]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth3:");              //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(durchnittswert_hall[3]); //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins

  delay(10); //  WartezeiT
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE)
  {

    if (rx_frame.FIR.B.FF == CAN_frame_std)
    {
      printf("New standard frame");
    }
    else
    {
      printf("New extended frame");
    }

    if (rx_frame.FIR.B.RTR == CAN_RTR)
    {
      printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID, rx_frame.FIR.B.DLC);
    }
    else
    {
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID, rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++)
      {
        printf("0x%02X ", rx_frame.data.u8[i]);
      }
      printf("\n");
    }
  }
  // Send CAN Message
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x001;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x01;
  tx_frame.data.u8[2] = 0x02;
  tx_frame.data.u8[3] = 0x03;
  tx_frame.data.u8[4] = 0x04;
  tx_frame.data.u8[5] = 0x05;
  tx_frame.data.u8[6] = 0x06;
  tx_frame.data.u8[7] = 0x07;
  ESP32Can.CANWriteFrame(&tx_frame);

  if (durchnittswert_hall[0] > 19000 or durchnittswert_hall[1] > 19000)
  {
    leds[0] = CRGB(255, 0, 0);
  }
  else if (durchnittswert_hall[0] < 19000 && durchnittswert_hall[1] < 19000)
  {
    leds[0] = CRGB(0, 25, 0);
  }

  FastLED.show();

  delay(100);
}