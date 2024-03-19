int Rest = 12;
int Led = 13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(1000);
Serial.write("Begin");
digitalWrite(Led, HIGH);
delay(60000);
digitalWrite(Rest, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
