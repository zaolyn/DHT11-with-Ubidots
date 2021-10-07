#include <DHT.h> 
#include <UbidotsMicroESP8266.h> // import file ubidots  
#define DHTPIN 2  // mendefinisikan pin dht di nodemcu adalah 4, D2 = 4 
#define DHTTYPE DHT11 // mendefinisikan tipe dht yang kita gunakan


char auth[] = "BBFF-5HDpT5tzyT2vUMffjsL3VKZnFSDVws"; 
char pass[] = "HAU";
char ssid[] = "88888888";

DHT dht(DHTPIN,DHTTYPE);
Ubidots client(auth); // token client dari ubidotsnya
unsigned long last = 0;


void setup() {
  Serial.begin(9600);
  dht.begin(); // dht mulai membaca suhu dan kelembaban
  delay(20); // delay 0,02 detik
  client.wifiConnection(ssid,pass); // client konek ke wifi melalui ssid dan password

}

void loop() {
  if(millis()- last > 10000) {
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("Kelembaban", hum);
    client.add("suhu", temp);
    client.sendAll(true);
  }
}
