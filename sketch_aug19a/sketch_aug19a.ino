#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <DS3231.h>
#include <SPI.h>
#include <SD.h>

#define DHTPIN 9
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
DS3231 rtc(SDA, SCL);

Time t;
bool SDInit = true;

void setup() {
  pinMode(7, INPUT);
  delay(2000);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  rtc.begin();
  dht.begin();
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    SDInit = false;
  } else {
    Serial.println("initialization done.");
  }
  writedata();
}

void loop() {
  delay(2000);

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  if (isnan(hum) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hic = dht.computeHeatIndex(temp, hum, false);

  String csvString = String(hum) + "," + String(temp) + "," + String(hic) + ",";
  csvString += rtc.getTimeStr() + String(" ") + rtc.getDateStr() + "," + String(digitalRead(7));
  Serial.println(csvString);

  File dataFile = SD.open("weather.csv", FILE_WRITE);
  if (SDInit) {
    if (dataFile) {
      dataFile.println(csvString);
      dataFile.close();
    } else {
      Serial.println("error opening datalog.txt");
      SDInit = false;
    }
  }
  delay(10000);
}
void writedata() {

}
