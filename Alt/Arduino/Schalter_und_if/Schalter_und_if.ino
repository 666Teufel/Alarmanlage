int Knopf = 12;
int Schalterzustand;


void setup() {
  // put your setup code here, to run once:
pinMode(Knopf,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
Schalterzustand = digitalRead(Knopf);
if (Schalterzustand == 1){

}

}
