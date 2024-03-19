int Ledg = 9;
int Ledb = 8;
int Ledr = 3;
int Ledg1 = 1;
int Ledg2 = 1;
int Led;
void setup() {
  // put your setup code here, to run once:
pinMode(Ledg, OUTPUT);
pinMode(Ledb, OUTPUT);
pinMode(Ledr, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

analogWrite(Ledr, 0);
analogWrite(Ledb, 0);
analogWrite(Ledg, Led);
delay(100);
Led =Led + Ledg2;
if(Led > 255 || Led < 0) {
  Led = -Led;
}
}
