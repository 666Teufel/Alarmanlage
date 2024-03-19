int ROT = 2;
int GRUEN = 3;
int BLAU = 4;
void setup(){
pinMode(ROT, OUTPUT);
pinMode(GRUEN, OUTPUT);
pinMode(BLAU, OUTPUT);
}
void loop(){
digitalWrite(ROT, HIGH);
digitalWrite(GRUEN, LOW);
digitalWrite(BLAU, LOW);
delay(500);
digitalWrite(ROT, LOW);
digitalWrite(GRUEN, HIGH);
digitalWrite(BLAU, LOW);
delay(500);
digitalWrite(ROT, LOW);
digitalWrite(GRUEN, LOW);
digitalWrite(BLAU, HIGH);
delay(500);
digitalWrite(ROT, HIGH);
digitalWrite(GRUEN, HIGH);
digitalWrite(BLAU, LOW);
delay(500);
digitalWrite(ROT, LOW);
digitalWrite(GRUEN, HIGH);
digitalWrite(BLAU, HIGH);
delay(500);
digitalWrite(ROT, HIGH);
digitalWrite(GRUEN, HIGH);
digitalWrite(BLAU, HIGH);
delay(500);
digitalWrite(ROT, HIGH);
digitalWrite(GRUEN, LOW);
digitalWrite(BLAU, HIGH);
delay(500);
}
