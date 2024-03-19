// library
#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int a = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("device is ready...");
pinMode(11, OUTPUT);
  vw_set_rx_pin(12);
  vw_setup(1000); // bps
  vw_rx_start();
}

void loop()
{
  if (vw_get_message(message, &messageLength)) // non-blocking
  {
    for (int i = 0; i < messageLength; i++)
    {
      Serial.write(message[i]);
    }
a = message;
  
  if (a == 1){
    digitalWrite(11,HIGH);
  }
    if (a == 2){
    digitalWrite(11,LOW);
  }
  }
}
