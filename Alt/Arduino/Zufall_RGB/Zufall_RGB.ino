int Ledg = 9;
int Ledb = 11;
int Ledr = 10;
int d = 100;
int a = 30;
int Eingabe1 = 0;
int Eingabe2 = 100;
int Eingabe3 = 240;
int Zufallfaktor1 = 107;
int Zufallfaktor2 = 49;
int Modolu = 128;
void setup() {
  // put your setup code here, to run once:
pinMode(Ledg, OUTPUT);
pinMode(Ledb, OUTPUT);
pinMode(Ledr, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

Eingabe1 = Zufallfaktor1 * Eingabe1;
Eingabe1 = Zufallfaktor2 + Eingabe1;
Eingabe1 = Eingabe1 % Modolu;
delay(d);
Eingabe2 = Zufallfaktor1 * Eingabe2;
Eingabe2 = Zufallfaktor2 + Eingabe2;
Eingabe2 = Eingabe2 % Modolu;
delay(d);
Eingabe3 = Zufallfaktor1 * Eingabe3;
Eingabe3 = Zufallfaktor2 + Eingabe3;
Eingabe3 = Eingabe3 % Modolu;
delay(d);
delay(d);
analogWrite(Ledr, Eingabe1);
analogWrite(Ledb, Eingabe2);
analogWrite(Ledg, Eingabe3);
delay(d);
Serial.print("RGB:");
Serial.print(Eingabe1);
Serial.print(",");
Serial.print(Eingabe3);
Serial.print(",");
Serial.println(Eingabe2);
delay(a);
}
