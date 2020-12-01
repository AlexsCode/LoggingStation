#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "MiWifi 2.4"
#define STAPSK  "Allminenow00"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

//const int led = 13;


const int ir_A0 = A0;
const int ir_D0 = D0;
float analog_read_value;
bool digital_read_value;
String analog_read_value_string;


void handleRoot() {

  server.send(200, "text/plain", "hello from esp8266!");
  

}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);

}

void setup(void) {

  pinMode(ir_A0,INPUT);
  pinMode(ir_D0,INPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot); //push root
  
  server.on("/test", []() {
    server.send(200, "text/plain", "this works");
  }); // test header
  
  server.on("/alert", []() {
    analog_read_value = analogRead(ir_A0); //Reads Analogue Pin
    analog_read_value_string=String(analog_read_value);
    digital_read_value = digitalRead(ir_D0); //Reads Digital Pin to bool
    server.send(200, "text/plain", analog_read_value_string);
  }); // IO header

  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
