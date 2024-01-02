#include <Arduino.h>
// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6)
const int durchschnitts_berechnung_anzahl_der_werte = 10;

int Hallsensor_Werte[durchschnitts_berechnung_anzahl_der_werte];  // the readings from the analog input
int position_im_array = 0;          // the index of the current reading
int total = 0;              // the running total
int durchnittswert_hallsensor = 0;            // the average

const int Hallsensor_Pin = 34;

// variable for storing the potentiometer value
int an_hall_value = 0;
int min_value =10000;
int max_hall;
void Hall(){
    an_hall_value = analogRead(Hallsensor_Pin);

  Serial.print(">An_hall_value:");
  Serial.println(an_hall_value);
  
  max_hall = max(max_hall,an_hall_value);
  min_value = min(min_value,an_hall_value);
  Serial.print(">Max:");
  Serial.println(max_hall);
  Serial.print(">Min:");
  Serial.println(min_value);
    // subtract the last reading:
  total = total - Hallsensor_Werte[position_im_array];
  // read from the sensor:
  Hallsensor_Werte[position_im_array] = an_hall_value;
  // add the reading to the total:
  total = total + Hallsensor_Werte[position_im_array];
  // advance to the next position in the array:
  position_im_array = position_im_array + 1;

  // if we're at the end of the array...
  if (position_im_array >= durchschnitts_berechnung_anzahl_der_werte) {
    // ...wrap around to the beginning:
    position_im_array = 0;
  }

  // calculate the average:
  durchnittswert_hallsensor = total / durchschnitts_berechnung_anzahl_der_werte;
  // send it to the computer as ASCII digits
  Serial.print(">Smooth:");
  Serial.println(durchnittswert_hallsensor);
  delay(1);  // delay in between reads for stability
}
void setup() {
  Serial.begin(9600);
  delay(10000);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
    for (int thisReading = 0; thisReading < durchschnitts_berechnung_anzahl_der_werte; thisReading++) {
    Hallsensor_Werte[thisReading] = analogRead(Hallsensor_Pin);
    total = total + Hallsensor_Werte[thisReading];
    }
}

void loop() {
  Hall();
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");

  CAN.beginExtendedPacket(0x12);
  CAN.write('a'); //Buchstaben als nummern
  CAN.print(durchnittswert_hallsensor);
  CAN.endPacket();

  Serial.println("done");

  delay(10);

}
