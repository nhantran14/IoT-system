#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include "string.h"
#include <WiFiManager.h>
SoftwareSerial mySerial(1, 3); 

const char* mqttServer = "210.86.239.240";
// const int mqttPort = 8080;
WiFiManager wifiManager;
WiFiClient espClient;
PubSubClient client(espClient);
String rsp1,rsp2,rsp3;
int state = 0;
int itv = 2000;

void callback(char* topic, byte* payload, unsigned int length) {
  if ((char)payload[0] == '1' && (char)payload[2] == 'n') mySerial.println("1on");
  if ((char)payload[0] == '1' && (char)payload[2] == 'f') mySerial.println("1off");
  if ((char)payload[0] == '2' && (char)payload[2] == 'n') mySerial.println("2on");
  if ((char)payload[0] == '2' && (char)payload[2] == 'f') mySerial.println("2off");
  if ((char)payload[0] == '3' && (char)payload[2] == 'n') mySerial.println("3on");
  if ((char)payload[0] == '3' && (char)payload[2] == 'f') mySerial.println("3off");
  if (memcmp(payload,"wifi_rst",8) == 0) {
    while (wifiManager.getWiFiSSID() != "") wifiManager.resetSettings();
    wifiManager.startConfigPortal();
    }
  if (memcmp(payload,"itv=",4) == 0) itv = (payload[4] - 0x30) * 1000;
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      client.subscribe("nhanhung/command");
    }
  }
}

void setup()
{  
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);    
  pinMode(15,INPUT);
  // setup_wifi();
  client.setServer(mqttServer, 8080);
  client.setCallback(callback);
}

void loop()
{
  if (!wifiManager.autoConnect()) wifiManager.startConfigPortal();
  state = digitalRead(15);
  if (state == 1) {
    digitalWrite(BUILTIN_LED, LOW);
    mySerial.println("1a");
    delay(itv);
    rsp1 = mySerial.readStringUntil('\n');

    mySerial.println("2a");
    delay(itv);
    rsp2 = mySerial.readStringUntil('\n');

    mySerial.println("3a");
    delay(itv);
    rsp3 = mySerial.readStringUntil('\n');
    client.publish("nhanhung/gateway1/sensor1", rsp1.c_str());
    client.publish("nhanhung/gateway1/sensor2", rsp2.c_str());
    client.publish("nhanhung/gateway1/sensor3", rsp3.c_str());
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
    mySerial.println("1b");
    delay(itv);
    rsp1 = mySerial.readStringUntil('\n');

    mySerial.println("2b");
    delay(itv);
    rsp2 = mySerial.readStringUntil('\n');

    mySerial.println("3b");
    delay(itv);
    rsp3 = mySerial.readStringUntil('\n');
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
