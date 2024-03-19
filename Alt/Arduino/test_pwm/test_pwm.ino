int a = 9;
int b = 0;
int c = 10;

void setup() {
  // put your setup code here, to run once:
pinMode(a, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite( a, b);
b = b + c;

if(b > 255 || -b < 0) {
  b = -b;
     }
delay(1000);     
}
