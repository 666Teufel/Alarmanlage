int sensorWert = 0;
int sensorWert1 = 0;
int Laser1 = 10;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Laser1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorWert = analogRead(A0);
sensorWert1 = analogRead(A1);
Serial.println(sensorWert);
Serial.println(sensorWert1);
analogWrite(Laser1, 255);
if( sensorWert < 830 || sensorWert > 970){
Serial.println("Alarm");
Serial.println(sensorWert);
}
}
