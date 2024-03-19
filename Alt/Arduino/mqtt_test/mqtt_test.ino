//Datenbereitstellung ueber MQTT mit NodeMCU ESP8266
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN D2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Box unten";
const char* password = "Fleur Husnik";
const char* mqtt_server = "192.168.188.62";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.begin(115200);
  Serial.println();
  Serial.print("Verbindung zu ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA); //Arbeite nur als Station und nicht als AccessPoint
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Nachricht angekommen [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-dht11";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      //client.subscribe("outtemp"); aboniere folgendes Thema
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  // read DHT11 sensor every 10 seconds
  if (now - lastMsg > 40000) {
    lastMsg = now;

    //int chk = DHT.read11(DHT11_PIN);
     String msg="";

     char MsgTemp[25];
     char MsgFeutigkeit[25];     
 
     msg= dht.readTemperature();
     //msg=msg+"Â°C";
     msg.toCharArray(MsgTemp,25); 
         
     msg= dht.readHumidity();
     //msg=msg+"%";
     msg.toCharArray(MsgFeutigkeit,25);  

          
     client.publish("Temp", MsgTemp);
     client.publish("Feuchtigkeit", MsgFeutigkeit);

  }
}
