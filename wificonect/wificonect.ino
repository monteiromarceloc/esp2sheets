#include <esp8266wifi.h>
#include <esp8266httpclient.h>

const char* ssid = "yourNetworkName";
const char* password = "yourNetworkPassword";
 
void setup () {

Serial.begin(115200);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
