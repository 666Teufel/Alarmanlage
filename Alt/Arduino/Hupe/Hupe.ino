int Hupe = 12;
int Pause = 1;// Pause in Sekunden
int Pause1 = 1;// Pause in Sekunden
void setup() {
  // put your setup code here, to run once:
pinMode(Hupe , OUTPUT);
Pause = Pause * 1000;
Pause1 = Pause1 * 1000;
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(Pause);
digitalWrite(Hupe , HIGH);
delay(Pause);
digitalWrite(Hupe , LOW);
delay(Pause1);
}
