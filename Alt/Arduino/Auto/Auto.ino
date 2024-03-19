int Rechts1 = 12;
int Rechts2 = 3;
int Lings1 = 11;
int Lings2 = 2;
int zahler = 1000;
void setup() {
  // put your setup code here, to run once:
pinMode(Rechts1, OUTPUT);
pinMode(Lings1, OUTPUT);
pinMode(Rechts2, OUTPUT);
pinMode(Lings2, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(zahler);
 re();
 delay(zahler);
 warten();
 delay(zahler);
 lings();
 delay(zahler);
 warten();
 delay(zahler);
 //zahler = zahler + 5;
 if (zahler > 1000) {
  zahler = 20;
 }
 
}
void re(){
  Serial.println("rechts");
 digitalWrite(Lings1, 0);
 digitalWrite(Lings2, 0);
 digitalWrite(Rechts1, 1);
 digitalWrite(Rechts2, 1);
}
void lings(){
    Serial.println("lings");
 digitalWrite(Rechts1, 0);
 digitalWrite(Rechts2, 0);
 digitalWrite(Lings1, 1);
 digitalWrite(Lings2, 1);

}
void warten(){
    Serial.println("warten");
 digitalWrite(Lings1, 0);
 digitalWrite(Lings2, 0);
 digitalWrite(Rechts1, 0);
 digitalWrite(Rechts2, 0);
}
