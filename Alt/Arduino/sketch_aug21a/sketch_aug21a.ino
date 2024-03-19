int a =  0;
int b = 10;
int Led = 11;
void setup() {
  // put your setup code here, to run once:
pinMode(Led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
a = a + b
;if (a > 60 || -a < 0)  {
digitalWrite(Led, HIGH);
a = -a;
delay(10000);
digitalWrite(Led, LOW);
}
delay(1000);
}
