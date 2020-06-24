#include <DHT.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
DHT dht(D2,DHT11);
char ip[] = "184.106.153.149";  // ip of thingspeak
long id = 1079319;
const char* api = "90A5OCW4XG8WUSSN";
const char* ssid = "Ajay";   // wifi name
const char* pass = "Preetididi@6";   // wifi password
WiFiClient client;
float t,h;
void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to Wifi");
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("WiFi Connected");
  ThingSpeak.begin(client);
  dht.begin();
}

void loop() {
 if(client.connect(ip,80)){
    t = dht.readTemperature();
    h = dht.readHumidity();
    Serial.println("Temperature -");
    Serial.println(t);
    Serial.println("Humidity -");
    Serial.println(h);
  }
  ThingSpeak.setField(1,h);
  ThingSpeak.setField(2,t);
  ThingSpeak.writeFields(id,api);
  client.stop();
  delay(10000);
}
