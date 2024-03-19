int upButton = 2;
int Ledr = 9;
int Ledg = 6;
int Ledb = 3;
int Ledrz = 0;
int Ledgz = 0;
int Ledbz = 255;
int r = 0;
int pr = 0;
int g = 0;
int pg = 0;
int b = 0;
int pb = 0;
long Pause = 3600000;
void setup() {
  // put your setup code here, to run once:
pinMode(upButton, INPUT_PULLUP);
pinMode(Ledr, OUTPUT);
pinMode(Ledg, OUTPUT);
pinMode(Ledb, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(upButton)){
    analogWrite(Ledr, Ledrz);
    analogWrite(Ledg, Ledgz);
    analogWrite(Ledb, Ledbz);
    delay(Pause);
    analogWrite(Ledr, 0);
    analogWrite(Ledg, 0);
    analogWrite(Ledb, 0);
  }
  r = Ledrz - 1;
  pr = Ledrz + 1;
  Ledrz = random(r,pr);
  if(Ledbz < 0) {
    Ledbz++;
  }
    if(Ledbz > 255) {
    Ledbz--;
  }
    b = Ledbz - 1;
  pb = Ledbz + 1;
  Ledbz = random(b,pb);
  if(Ledbz < 0) {
    Ledbz++;
  }
    if(Ledbz > 255) {
    Ledbz--;
  }
    b = Ledbz - 1;
  pb = Ledbz + 1;
  Ledbz = random(b,pb);
  if(Ledbz < 0) {
    Ledbz++;
  }
    if(Ledbz > 255) {
    Ledbz--;
  }
}
