#include <Arduino.h>
// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
int a_avarage;
#include <CAN.h>

void setup()
{
  Serial.begin(9600);
  delay(10000);
  while (!Serial)
    ;

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3))
  {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }
}

void loop()
{
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize != 0 || CAN.packetId() != -1 && packetSize != 0)
  {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended() && packetSize != 0)
    {
      Serial.print("extended ");
    }

    if (CAN.packetRtr() && packetSize != 0)
    {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr() && packetSize != 0)
    {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    }
    else
    {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      if ((char)CAN.read() = 'a')
      {
        while (CAN.available())
        {
          a_avarage = (int)CAN.read();
          Serial.println(a_avarage);
        }
        Serial.println();
        Serial.println(a_avarage);
        Serial.println();
      }
    }

    Serial.println();
  }
}