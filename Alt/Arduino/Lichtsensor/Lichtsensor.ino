int sensorWert = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(53, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);
    pinMode(5, OUTPUT);
  digitalWrite(53 ,HIGH);
  digitalWrite(52 ,HIGH);
  digitalWrite(51 ,HIGH);
  digitalWrite(50 ,HIGH);
  digitalWrite(5 ,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorWert = analogRead(A0);
Serial.println(sensorWert);

}
