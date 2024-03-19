#include <SoftwareSerial.h>

char Incoming_value = 0;
                
void setup() 
{
  Serial.begin(9600);         
  pinMode(12, OUTPUT);
  pinMode(8, INPUT); 
  serialbluetooth.begin(9600);
  Serial.begin(9600);      
}

void loop()
{
if(serialbluetooth.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1')             
      digitalWrite(12, HIGH);  
    else if(Incoming_value == '0')       
      digitalWrite(12, LOW);   
  } 
  delay(1020);                           
} 
