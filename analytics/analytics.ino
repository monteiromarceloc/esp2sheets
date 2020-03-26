#include "DHT.h"
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "NOME DO WIFI"
#define STAPSK  "SENHA"
#endif
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(STASSID, STAPSK);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    delay(2000);
    measureHumidityAndTemperature();
  } else {
    delay(10000);
  }
}

void measureHumidityAndTemperature() {
  static float currentTemperature = 0;

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(h);
    Serial.println(t);
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float diff = difference(currentTemperature, t);
  if(currentTemperature != t && diff > 0.1) {
    currentTemperature = t;
    Serial.print(F("New currentTemperature: "));
    Serial.println(currentTemperature);
  }

  Serial.print(F("currentTemperature: "));
  Serial.print(currentTemperature);
  Serial.print(F(" Measured Humidity: "));
  Serial.print(h);
  Serial.print(F("% Measured Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));  
}

void serveGrowerData() {

}

float difference(float a, float b) {
  if(a > b){
    return (a - b);
  } else {
    return (b - a);
  }
}
