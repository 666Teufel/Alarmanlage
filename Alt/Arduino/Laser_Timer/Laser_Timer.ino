int Ledg = 9;
int Ledb = 11;
int Ledr = 10;
int d = 1000;
int a = 15000;

void setup() {
  // put your setup code here, to run once:
pinMode(Ledg, OUTPUT);
pinMode(Ledb, OUTPUT);
pinMode(Ledr, OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(5000);

digitalWrite(13, HIGH);
analogWrite(Ledr, 255);
delay(d);
analogWrite(Ledr, 0);
analogWrite(Ledb, 255);
delay(d);
analogWrite(Ledb, 0);
analogWrite(Ledg, 255);
delay(d);
analogWrite(Ledg, 0);
delay(a);
analogWrite(5, 120);
}
