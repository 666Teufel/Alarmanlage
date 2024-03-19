#include "DHT.h"

#define DHTPIN 11 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int r = 3;
int g = 4;
int b = 6;
int staerke;
int relay = 12;
void setup() {
  pinMode(r , OUTPUT);
  pinMode(g , OUTPUT);
  pinMode(b , OUTPUT);
  pinMode(relay , OUTPUT);
  Serial.begin(9600);
  Serial.println("Start");
  dht.begin();
  analogWrite(r , 255);
  analogWrite(g , 255);
  analogWrite(b , 255);
  digitalWrite(relay , LOW);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
 float t = dht.readTemperature();
   if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  delay(100);
  analogWrite(r , 255);
  analogWrite(g , 255);
  analogWrite(b , 255);
  digitalWrite(relay , LOW);
  delay(100);
  analogWrite(r , 0);
  analogWrite(g , 0);
  analogWrite(b , 0);
    return;
  }
  if((t)<= 30){
    digitalWrite(relay , HIGH);
    analogWrite(r , 0);
    analogWrite(g , 0);
    analogWrite(b , staerke);
    Serial.println("gut");
  }
  
  if((t)<= 40 && (t)> 30){
    digitalWrite(relay , HIGH);
    analogWrite(r , 0);
    analogWrite(g , staerke);
    analogWrite(b , 0);
  }
  
  if((t)<= 46 && (t)> 40){
    digitalWrite(relay , HIGH);
    analogWrite(r , staerke);
    analogWrite(g , 0);
    analogWrite(b , 0);
  }
  if((t) > 46){
    digitalWrite(relay , LOW);
    analogWrite(r , staerke);
    analogWrite(g , staerke);
    analogWrite(b , staerke);
    while((t) > 28){
    float t = dht.readTemperature();
    Serial.println(t);
    delay(300000);  
    }
    
  }
  Serial.println(t);
  delay(2000);
}
