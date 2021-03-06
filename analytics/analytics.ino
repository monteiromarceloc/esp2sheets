#include "DHT.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <RtcDS3231.h>
#include <RtcDateTime.h>

#ifndef STASSID
#define STASSID "NOME DO WIFI"
#define STAPSK  "SENHA"
#define API_BASE_URL "http://54.233.92.165:8080"
#endif
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
RtcDS3231<TwoWire> Rtc(Wire);

void configureDHT() {
  dht.begin();
}

void configureRTC() { 
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
}

void connectToWifi() {
  WiFi.begin(STASSID, STAPSK);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  connectToWifi();
  configureRTC();
  configureDHT();
}

void loop() {
  bool isConnectedToWifi = (WiFi.status() == WL_CONNECTED);
  if (isConnectedToWifi) {
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
  if(currentTemperature != t && diff >= 0.5) {
    currentTemperature = t;
    Serial.print(F("New currentTemperature: "));
    Serial.println(currentTemperature);
    serveGrowerData(t, h);
  }

  Serial.print(F("currentTemperature: "));
  Serial.print(currentTemperature);
  Serial.print(F(" Measured Humidity: "));
  Serial.print(h);
  Serial.print(F("% Measured Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));  
}

void serveGrowerData(float temperature, float humidity) {
  RtcDateTime now = Rtc.GetDateTime();
  WiFiClient client;
  HTTPClient http;
  http.begin(client, API_BASE_URL "/analytics/serveGrowerData");
  http.addHeader("Content-Type", "application/json");  //Specify content-type header
  char payload[128];
  // mounting JSON payload in string format
  snprintf(payload, sizeof(payload), "{\"temperature\":%.2f, \"humidity\":%.2f, \"timestamp\":%d000}", temperature, humidity, now.Epoch64Time());
  int httpCode = http.POST(payload);    // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      Serial.println("...Saved!");
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

float difference(float a, float b) {
  if(a > b){
    return (a - b);
  } else {
    return (b - a);
  }
}
