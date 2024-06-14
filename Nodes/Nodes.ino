#include <DHT.h>
#include <dht11esp8266.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(1, 3); 
#define DHT11PIN 14
#define DHTType DHT11
DHT HT(DHT11PIN, DHTType);

int humi,temp;
const char* id1a = "1a";
const char* id2a = "2a";
const char* id3a = "3a";
const char* id4a = "4a";
const char* id1b = "1b";
const char* id2b = "2b";
const char* id3b = "3b";
const char* id4b = "4b";
const char* on = "2on";
const char* off = "2off";
char all[200];

void setup()
{  
  HT.begin();
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop()
{
  humi = (int)HT.readHumidity() + 0;
  temp = (int)HT.readTemperature() + 0;
  String rsp = mySerial.readStringUntil('\n');
  if (strstr(rsp.c_str(),id2a) != NULL) {
    sprintf(all,"{\"id\": \"device2a\",\"temperature2\": \"%d\",\"humidity2\": \"%d\"}", temp, humi);
    mySerial.println(all);
  }
  if (strstr(rsp.c_str(),id2b) != NULL) {
    sprintf(all,"{\"id\": \"device2b\",\"temperature2\": \"%d\",\"humidity2\": \"%d\"}", temp, humi);
    mySerial.println(all);
  }
  if (strstr(rsp.c_str(),on) != NULL) {
    digitalWrite(BUILTIN_LED, LOW);
  }
  if (strstr(rsp.c_str(),off) != NULL) {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}
