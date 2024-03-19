int Knopf = 12;
int Schalterzustand;
int r = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(Knopf,INPUT);
Serial.begin(9600); 
pinMode(r,OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
Schalterzustand = digitalRead(Knopf);
if (Schalterzustand == 1){
   digitalWrite(r, HIGH);
}
digitalWrite(r,LOW);
}
