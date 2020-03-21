#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDateTime.h>
#include <RtcDS3231.h>
#include <RtcTemperature.h>

// Controled variables
#define LEDS_ON_HOUR 6
#define LEDS_OFF_HOUR 18

// datasheet: https://blog.eletrogate.com/nodemcu-esp12-introducao-1/
// alias: https://mechatronicsblog.com/esp8266-nodemcu-pinout-for-arduino-ide/

#define LEDS 12          // D6 - GPI12
#define EXAUSTOR 8       //
#define SEN_LUZ 3
#define SEN_TEMP 4
#define SEN_TEMP_AR 5
#define SEN_HUM_AR 6
#define SEN_HUM_SOLO 7

#define BOMBA 1

RtcDS3231<TwoWire> Rtc(Wire);
int hh=0,mm=0;

void setup() {

  pinMode(LEDS, OUTPUT);
  // RTC Time
  Serial.begin(115200);           
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  // if (!Rtc.IsDateTimeValid() || !Rtc.isrunning()) {
  // Serial.println("RTC lost confidence in the DateTime!");
  
  // Set Date and Time no matter what
    Rtc.SetDateTime(compiled);
    
  // }

  // wifi conection
}

void loop() {
  // get sensors data
  // get global time
  RtcDateTime now = Rtc.GetDateTime();
  printTime(now);
  
  // set led
  int hr = now.Hour();
  bool LedsOn = (hr >= LEDS_ON_HOUR && hr < LEDS_OFF_HOUR);
  digitalWrite(LEDS, LedsOn);

  // set bomb
  // set exaustor

  // timer bomba
  // timer exaustor

  // send data via wifi
  delay(1000);
}

void printTime(RtcDateTime rtcTime){
  Serial.print(rtcTime.Year(), DEC);
  Serial.print('/');
  Serial.print(rtcTime.Month(), DEC);
  Serial.print('/');
  Serial.print(rtcTime.Day(), DEC);
  Serial.print(" ");
  Serial.print(rtcTime.Hour(), DEC);
  Serial.print(':');
  Serial.print(rtcTime.Minute(), DEC);
  Serial.print(':');
  Serial.println(rtcTime.Second(), DEC);
  Serial.println();
}

void blinkLed(int pin){
  digitalWrite(pin, HIGH);
  Serial.println("Leds High");
  delay(1000);
  digitalWrite(pin, LOW);
  Serial.println("Leds Low");
  delay(1000);
}
