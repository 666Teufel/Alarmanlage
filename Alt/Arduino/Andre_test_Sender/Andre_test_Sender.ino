#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9);
const byte address[6] = "00001";
byte EingangsSignal = 0;

void setup() {
  // put your setup code here, to run once:
radio.begin(); // Start der 2,4 GHz Wireless Kommunikation
radio.openWritingPipe(address); // Setzen der Sendeadresse zur Übermittlung der Daten
radio.setPALevel(RF24_PA_HIGH); // Leistung des NRF Moduls je nach Entfernung kann man von MIN bis MAX einstellen (MAX,HIGH,LOW,MIN)
radio.stopListening(); // Das angeschlossene Modul wird als Sender konfiguriert

pinMode(7 , INPUT); // Port zum Einlesen des Schalterzustandes/Eingangssignals konfigurieren


}

void loop() {
  // put your main code here, to run repeatedly:
EingangsSignal = digitalRead(7); // Einlesen des Eingangssignals von Pin 7 des Arduinos
radio.write(&EingangsSignal, sizeof(EingangsSignal)); //Senden des Schalterstatus zum Empfänger
}
