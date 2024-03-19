#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <OneWire.h>
#include <DallasTemperature.h>
// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 1 //Temperatursensor DS18B20

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

#include <FastGPIO.h>

//Schweiß Pins
//const int Mosfet_IN_Pin = 2;
const int Mosfet_EN_Pin = 3;

//Eingabe Geräte Pins
const int Pot_SW_Pin = 4;
const int Footpedal_IN_Pin = 5;
const int BTN1_IN_Pin = 6;
const int BTN2_IN_Pin = 7;

//Digitale Eingabe
boolean Pot_SW;
boolean Footpedal;
boolean BTN1;
boolean BTN2;

//Led Pin
const int WS2812_Pin = 8;

//Mosfet Pin Laden/Entladen und Enable des Kondensators
const int Mosfet_Cap_Charge_Pin = 9;
const int Mosfet_Cap_Discharge_Pin = 10;
const int Mosfet_Cap_EN_Pin = 11;

//Analoge Eingabe
const int Cap_VTG_DIV_Pin = A0;
const int Pot_VTG_Pin = A1;
const int Neg_Weld_Check_Pin = A2;

//Analoge Eingabe
int Cap_VTG_DIV;
int Pot_VTG;
int Neg_Weld_Check;

//Zeit Gespeichert
int Zeit_Weld;


Adafruit_NeoPixel pixels(1, WS2812_Pin, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();// Bei Henry
//  lcd.init();//Bei Luis
  lcd.backlight();

  


  //Output
  //pinMode(Mosfet_IN_Pin, OUTPUT);
  pinMode(Mosfet_EN_Pin, OUTPUT);
  pinMode(WS2812_Pin, OUTPUT);
  pinMode(Mosfet_Cap_EN_Pin, OUTPUT);
  pinMode(Mosfet_Cap_Discharge_Pin, OUTPUT);
  pinMode(Mosfet_Cap_Charge_Pin, OUTPUT);

  //Input
  pinMode(Pot_SW_Pin, INPUT_PULLUP);
  pinMode(Footpedal_IN_Pin, INPUT_PULLUP);
  pinMode(BTN1_IN_Pin, INPUT_PULLUP);
  pinMode(BTN2_IN_Pin, INPUT_PULLUP);

  sensors.begin(); //1Wire
  digitalWrite(Mosfet_Cap_EN_Pin, HIGH);
  digitalWrite(Mosfet_EN_Pin, HIGH);

  pixels.begin();
  pixels.clear();
}


int prev_Footpedal = false;


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Sensor: ");
  Sensor_Check();
  Serial.println();
  digitalWrite(Mosfet_Cap_Charge_Pin, HIGH);
  //Temp();
  if (Pot_VTG<20) {
    digitalWrite(Mosfet_Cap_Discharge_Pin, HIGH);
    digitalWrite(Mosfet_Cap_Charge_Pin, LOW);
    pixels.setPixelColor(0, pixels.Color(10, 10, 10));
    pixels.show(); 
  }
  else{
    if (Footpedal == true && prev_Footpedal == false) {
      prev_Footpedal = true;
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      pixels.show(); 
      digitalWrite(Mosfet_Cap_Charge_Pin, LOW);
      delay(10);
      FastGPIO::Pin<2>::setOutput(HIGH);
      delayMicroseconds(Zeit_Weld);
      FastGPIO::Pin<2>::setOutput(LOW);
    }
    if(Footpedal == false){
      delay(1000);
      prev_Footpedal = false;
    }

    
    digitalWrite(Mosfet_Cap_Charge_Pin, HIGH);
    digitalWrite(Mosfet_Cap_Discharge_Pin, LOW);
    Zeit_Weld=60;//Pot_VTG*0.05;
    lcd.setCursor(0, 1);
    lcd.print(Zeit_Weld);
    lcd.print(" ");
  }
}

//Sensoren Überprüfen
void Sensor_Check() {
  //Digital
  Pot_SW = digitalRead(Pot_SW_Pin);
  Serial.print("Pot_SW: ");
  Serial.println(Pot_SW);

  Footpedal = digitalRead(Footpedal_IN_Pin);
  Serial.print("Footpedal: ");
  Serial.println(Footpedal);

  BTN1 = digitalRead(BTN1_IN_Pin);
  Serial.print("BTN1: ");
  Serial.println(BTN1);

  BTN2 = digitalRead(BTN2_IN_Pin);
  Serial.print("BTN2: "); Serial.println(BTN2);

  //Analog
  Cap_VTG_DIV = analogRead(Cap_VTG_DIV_Pin);
  Serial.print("Cap_VTG_DIV: "); Serial.println(Cap_VTG_DIV);

  if(Pot_VTG>=20){
    if(Cap_VTG_DIV>=900){
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
      pixels.show();
    }
    else{
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.show(); 
    }
  }
  
  
  lcd.setCursor(0, 0);
  lcd.print(Cap_VTG_DIV);


  
  //Pot_VTG = analogRead(Pot_VTG_Pin);                      //FIXME
  Pot_VTG = 60;
  
  Serial.print("Pot: "); Serial.println(Pot_VTG);
  Neg_Weld_Check = analogRead(Neg_Weld_Check_Pin);
  Serial.print("Neg_Weld_Check: "); Serial.println(Neg_Weld_Check);
  lcd.setCursor(0, 1);
  lcd.print(Neg_Weld_Check);
}

void Temp() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device

  // Print the temperature in Celsius in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C  |  ");
}
