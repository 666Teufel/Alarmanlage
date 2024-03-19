int Ledb = 9;
int a;
int b = 1;
int Knopf = 11;
int Schalterzustand;

void setup() {
  // put your setup code here, to run once:
 pinMode(Ledb, OUTPUT);
 pinMode(Knopf,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Schalterzustand = digitalRead(Knopf);


if (Schalterzustand == 1){
a = a + b;
}
delay(10);
analogWrite(Ledb, a);
}
