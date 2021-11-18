#include <DHT.h>
#include <UbidotsMicroESP8266.h> // import file ubidots

#define DHTPIN 4 // mendefinisikan pin dht di nodemcu adalah 4, D2 = 4
#define DHTTYPE DHT11 // mendefinsikan tipe dht yang kita gunakan

char auth[] = "BBFF-nHf4Hu7s1OXXsrjJHMOhfLfsg5LMzq";
char ssid[] = "NamaHostpotmu";
char pass[] = "PasswordHostpotmu";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth); // setting token client di ubidots
unsigned long last = 0;

void setup() {
  Serial.begin(9600);
  dht.begin(); // dht mulai membaca suhu dan kelembapan
  delay(20); // delay 0,O2 detik
  client.wifiConnection(ssid, pass); // menyambungkan ubidots client dengan wifi

}

void loop() {
  if (millis() - last > 10000) { // jika sudah 10 detiks
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("kelembapan",hum); // ubidots client membaca kelembapan
    client.add("Temprature",temp); // ubidots client membaca suhu
    client.sendAll(true); //ubidots client mengirimkan semua data
  }
}
