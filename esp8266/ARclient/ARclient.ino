#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "ARDEMO";
const char* password = "12345678";

ESP8266WebServer server(80);

const int led = D2;
int stat = 1;

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, stat);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("");
  Serial.println("");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("");

  server.on("/led", [](){
    server.send(200, "text/plain", "OK");
    if (stat > 0) {
      stat = 0;
    } else {
      stat = 1;
    }
    digitalWrite(led, stat);
    Serial.print("LED=");
    Serial.println(stat);
 });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
