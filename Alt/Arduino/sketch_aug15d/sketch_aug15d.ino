int a = 8;

void setup() {
  // put your setup code here, to run once:
pinMode(a, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite( a, 255);
delay(1000);     
}
