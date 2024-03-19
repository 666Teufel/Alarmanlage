int BLAU = 9;
int a = 20;
int b =0;
void setup() {
  // put your setup code here, to run once:
pinMode(BLAU, OUTPUT);
}

void loop() {
analogWrite(BLAU, b);
b = b + a;
if(b > 100 || b < 0){
b = -b;
}

}
