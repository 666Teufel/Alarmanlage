#include <avr/wdt.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Reset");
 wdt_disable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:

}
