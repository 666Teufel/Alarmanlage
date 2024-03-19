#include <Arduino.h> // hinzufügen von Arduino Bibliothek
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_ADS1X15.h> // hinzufügen von Adafruit_ADS1X15 Bibliothek
#include <Wire.h>
#define I2C_SDA 8
#define I2C_SCL 9
Adafruit_ADS1115 ads;           /* Use this for the 16-bit version */
#define ADS1115I2C_ADDRESS 0x48 // I2C Adresse des ADS1115

//  Hinzufügen von Variabeln
int16_t adc0, adc1; //  Variabeln für die Messwerte des ADS1115

void setup()
{
  Serial.begin(115200); //  Starten der Serial Port
  Wire.begin(I2C_SDA, I2C_SCL);
  delay(10000); //  Wartezeit für das Starten der Serial Port
  Serial.println("Initializing ...");

  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
    while (1)
      ;
  }
}

void loop()
{
  adc0 = ads.readADC_SingleEnded(0); //  Messen des Hall Sensor Pins
  adc1 = ads.readADC_SingleEnded(1); //  Messen des Hall Sensor Pins
  Serial.print(">Smooth0:");         //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(adc0);              //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
  Serial.print(">Smooth1:");         //  Für Teleploter kennzeichnung das dieser Wert als Diagram dargestellt werden
  Serial.println(adc1);              //  Für Teleploter Ausgabe des durchschnittswert aller Messwertes des Hall Sensor Pins
}