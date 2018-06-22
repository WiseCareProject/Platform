#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <DHT.h>  //temp sensor library

const char* ssid = "wcnetwork";
const char* password = "wcnetwork";
const char* host = "192.168.4.1";
//const char* host = "192.168.25.223";

ESP8266WebServer server(80);
String myIP;
String myDevice = "environment";
float humidity =  -1;
float temperature = -1;
DHT dht;
bool heatBlanketFlag = false;
bool ventFlag = false;
String statusResponse;
bool sendRegistrationFlag = true;

//////////// ----------------- Function Declaration ----------------- ////////////
float getTemperature();
float getHumidity();
void temperatureController();
void turnOnBlanket();
void turnOffBlanket();
void turnOnVent();
void turnOffVent();
void setIpConfiguration();
//////////// ----------------- PINS Configuration ----------------- ////////////
const int DHT_PIN = 2;      // (D4)
const int blanketPIN = 13;  //d7
const int ventPIN = 12;     //D6

//////////// ----------------- Variables ----------------- ////////////

void setup()
{
  pinMode(ventPIN,OUTPUT);
  pinMode(blanketPIN,OUTPUT);
  digitalWrite(blanketPIN, HIGH);
  digitalWrite(ventPIN, LOW);

  dht.setup(DHT_PIN); // temp data pin 2
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  myIP = WiFi.localIP().toString();

  Serial.println("connect to WiFi network");
  if (MDNS.begin("esp8266"))
  {
   Serial.println("MDNS responder started");
  }
  //////////// ----------------- Routes ----------------- ////////////

    server.on("/tempStatus", []()               // CHECK & SEND TEMPERATURE
    {
      Serial.println("tempStatus");
      float tempStatus = getTemperature();
      statusResponse = String(tempStatus);
      Serial.println(statusResponse);
      server.send(200, "text/html", statusResponse);
    });
    server.on("/humidityStatus", []()          // CHECK & SEND humidity
    {
      Serial.println("humidityStatus");
      float humidityStatus = getHumidity();
      statusResponse = String(humidityStatus);
      Serial.println(statusResponse);
      server.send(200, "text/html", statusResponse);
    });
    server.on("/turnOnBlanket", []()          // TURN ON HEATING BLANKET BY COMMAND
    {
      Serial.println("turnOnBlanket COMMAND");
      turnOnBlanket();
      server.send(200, "text/html", "blanketON");
    });
    server.on("/turnOffBlanket", []()       // TURN OFF HEATING BLANKET BY COMMAND
    {
      Serial.println("turnOffBlanket COMMAND");
      turnOffBlanket();
      server.send(200, "text/html", "blanketOFF");
    });
    server.on("/turnOnVent", []()           // TURN ON VENT BY COMMAND
    {
      Serial.println("turnOnVent COMMAND");
      turnOnVent();
      server.send(200, "text/html", "ventON");
    });
    server.on("/turnOffVent", []()          // TURN OFF VENT BY COMMAND
    {
      Serial.println("turnOffVent COMMAND");
      turnOffVent();
      server.send(200, "text/html", "blanketOFF");
    });
    server.on("/checkTEMP", []()            // AUTOMATIC CHECK TENP & HUMIDITY
    {
      Serial.println("Check Temp COMMAND");
      temperatureController();
      server.send(200, "text/html", "");
    });
    server.on("/healthCheck", []()
    {
      Serial.println("healthCheck");
      server.send(200, "text/html", "healthCheckOK");
    });
    server.begin();
}
void loop()
{
  if(sendRegistrationFlag)
  {
    setIpConfiguration();
  }
  server.handleClient();
}

float getTemperature()
{
  temperature = dht.getTemperature();
  return temperature;
}
float getHumidity()
{
  humidity = dht.getHumidity();
  return humidity;
}
void temperatureController()
{
  float currentTemp = dht.getTemperature();
  float currentHumidity = dht.getHumidity();

  if(currentTemp >= 32 && currentHumidity >= 40)
  {
    turnOnVent();
    Serial.println("vent is on ");
  }
  if(currentTemp < 32 && currentTemp > 12)
  {
    turnOffVent();
    Serial.println("vent is off ");
  }
  if(currentTemp <= 12)
  {
    turnOnBlanket();
    Serial.println("blanket is on");
  }
  if(currentTemp >= 17)
  {
    turnOffBlanket();
    Serial.println("blanket is off ");
  }
}
void turnOnBlanket()
{
  digitalWrite(blanketPIN, LOW);
  heatBlanketFlag = true;
  Serial.println("blanket is ON");
  Serial.print("heatBlanketFlag = ");
  Serial.println(heatBlanketFlag);
}
void turnOffBlanket()
{
  digitalWrite(blanketPIN, HIGH);
  heatBlanketFlag = false;
  Serial.println("blanket is OFF");
  Serial.print("heatBlanketFlag = ");
  Serial.println(heatBlanketFlag);
}
void turnOnVent()
{
  digitalWrite(ventPIN, HIGH);
  ventFlag = true;
  Serial.println("vent is on ");
  Serial.print("ventFLAG = ");
  Serial.println(ventFlag);
}
void turnOffVent()
{
  digitalWrite(ventPIN, LOW);
  ventFlag = false;
  Serial.println("vent is off ");
  Serial.print("ventFLAG(off) = ");
  Serial.println(ventFlag);
}
void setIpConfiguration()
{
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 3000;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Requesting URL: ");
  Serial.println(host);
  client.print(String("GET ") + "/register?ip="+ myIP +"&device=" + myDevice + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" +"Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  sendRegistrationFlag = false;
}
