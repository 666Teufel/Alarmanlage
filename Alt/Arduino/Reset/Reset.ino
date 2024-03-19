unsigned long Zeit;
int Reset_pin = 2;
unsigned long Reset_timer = 1000;

unsigned long a = 2;
int Wochen = 0;
int Tage = 0;
int Stunden = 0;
int Minuten = 0;


void setup() {
Zeit = millis();
  
pinMode(Reset_pin, OUTPUT);
Serial.begin(9600);
Serial.println("9600");
}
void loop() {
Zeit = millis();

Serial.println(a);
a++;
Reset();
}
void Reset(){
  if(Zeit >= Reset_timer){
    digitalWrite(Reset_pin, HIGH);
  }
}
