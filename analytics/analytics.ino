#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  delay(2000);
  measureHumidityAndTemperature();
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

float difference(float a, float b) {
  if(a > b){
    return (a - b);
  } else {
    return (b - a);
  }
}
