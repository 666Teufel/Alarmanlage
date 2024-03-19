int Ledb = 12;
int Led;
void setup() {
  // put your setup code here, to run once:
pinMode(Ledb, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Led = 0;
do {
digitalWrite(Ledb, HIGH);
delay(1000);
digitalWrite(Ledb, LOW);
delay(1000);
} while (Led > 1999999); 
}
