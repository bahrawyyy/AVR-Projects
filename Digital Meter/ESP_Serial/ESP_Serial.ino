#include <ESP8266WiFi.h>
#include <WiFiClient.h>


const char *ssid = "Bahrawy"; //ESP Access Point
const char *password = "Bahrawy12345"; //ESP Password


WiFiClient client;
IPAddress ip (192, 168, 19, 2);
IPAddress netmask (255, 255, 255, 0);
const int port = 5210;
WiFiServer server(port);

void setup() {
  // THIS CODE WAS FINISHED ON JULY 30 2021
  Serial.begin(9600);
  delay(1000); //Wait to run ESP properly

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);

  Serial.println("Wifi Details:");
  Serial.println(ssid);
  Serial.println(password);
  Serial.println(WiFi.localIP());
  server.begin();
}



void loop() {
  if (!client.connected()) {
    client = server.available();
    return;
  }

  if (client.available() > 0) {
    String receivedData = client.readString();
    Serial.println(receivedData[0]);
  }

  if (Serial.available() > 0) {
    String sendData = Serial.readStringUntil(' ');
    // Once you see a space go to new line
    client.println(sendData);
  }
}


