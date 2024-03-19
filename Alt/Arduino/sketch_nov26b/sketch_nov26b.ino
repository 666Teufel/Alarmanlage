int Ledg = 9;
int Ledb = 11;
int Ledr = 10;
int d = 1000;
int Eingabe1 = 0;
int Eingabe2 = 100;
int Eingabe3 = 240;
int Zufallfaktor1 = 240;
int Zufallfaktor2 = 1000;
int Modolu = 255;
void setup() {
  // put your setup code here, to run once:
pinMode(Ledg, OUTPUT);
pinMode(Ledb, OUTPUT);
pinMode(Ledr, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

Eingabe1 = Zufallfaktor1 * Eingabe1;
Eingabe1 = Zufallfaktor2 + Eingabe1;
Eingabe1 = Eingabe1 % Modolu;
Eingabe2 = Zufallfaktor1 * Eingabe2;
Eingabe2 = Zufallfaktor2 + Eingabe2;
Eingabe2 = Eingabe2 % Modolu;
Eingabe3 = Zufallfaktor1 * Eingabe3;
Eingabe3 = Zufallfaktor2 + Eingabe3;
Eingabe3 = Eingabe3 % Modolu;


analogWrite(Ledr, Eingabe1);
analogWrite(Ledb, Eingabe2);
analogWrite(Ledg, Eingabe3);
delay(d);
}
