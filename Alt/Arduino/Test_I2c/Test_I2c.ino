int Wert = 0;
void setup() {
  // put your setup code here, to run once
  pinMode(53, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);
  digitalWrite(53 ,HIGH);
  digitalWrite(52 ,HIGH);
  digitalWrite(51 ,HIGH);
  digitalWrite(50 ,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
analogRead(A0);
delay(1000);
Wert = A0;
Serial.println(A0);
}
