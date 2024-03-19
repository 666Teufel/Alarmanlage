int sensorWert = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorWert = analogRead(A0);
Serial.println(sensorWert);
digitalWrite(12, HIGH);
}
