#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <DHT.h>  //temp sensor library

const char* ssid = "wisecare-WIFI";
const char* password = "123456789";
const char* host = "192.168.42.10";
ESP8266WebServer server(80);
String myIP;
String myDevice = "temperature";

float humidity =  -1;
float temperature = -1;
DHT dht;
bool heatBlanketFlag = false;
bool ventFlag = false;
//////////// ----------------- Function Declaration ----------------- ////////////
float getTemperature();
float getHumidity();
void temperatureController();
void turnOnBlanket();
void turnOffBlanket();
void turnOnVent();
void turnOffVent();
//////////// ----------------- PINS Configuration ----------------- ////////////
const int DHT_PIN = 2;      // ( D4)
const int blanketPIN = 13; //d7
const int ventPIN = 12; //D6

//////////// ----------------- Variables ----------------- ////////////

void setup()
{
  pinMode(ventPIN,OUTPUT);
  pinMode(blanketPIN,OUTPUT);
  Serial.begin(115200);
  delay(10);
  dht.setup(DHT_PIN); // temp data pin 2

  // Serial.println();
  // Serial.print("Connecting to ");
  // Serial.println(ssid);
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
  // myIP = WiFi.localIP().toString();
  //
  // Serial.println("connect to WiFi network");
  // if (MDNS.begin("esp8266"))
  // {
  //  Serial.println("MDNS responder started");
  // }
  //////////// ----------------- Routes ----------------- ////////////
    // server.on("/tempStatus", []()
    // {
    //   Serial.println("waterStatus");
    //   statusResponse = checkFlowtingSwitch();
    //   Serial.println(statusResponse);
    //   server.send(200, "text/html", statusResponse);
    // });
    // server.begin();
}
void loop()
{
  // Serial.print("Temperature = ");
  // Serial.println(getTemperature());
  // Serial.print("Humidity = ");
  // Serial.println(getHumidity());
turnOnVent();
turnOffBlanket();
delay(5000);
turnOffVent();
turnOnBlanket();
delay(5000);
Serial.println("");

  // if(sendRegistrationFlag)
  //   {
  //     Serial.print("connecting to ");
  //     Serial.println(host);
  //     WiFiClient client;
  //     const int httpPort = 8081;
  //     if (!client.connect(host, httpPort))
  //     {
  //       Serial.println("connection failed");
  //       return;
  //     }
  //     Serial.print("Requesting URL: ");
  //     Serial.println(host);
  //     client.print(String("GET ") + "/register?ip="+ myIP +"&device=" + myDevice + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" +"Connection: close\r\n\r\n");
  //     unsigned long timeout = millis();
  //     while (client.available() == 0)
  //     {
  //       if (millis() - timeout > 5000)
  //       {
  //         Serial.println(">>> Client Timeout !");
  //         client.stop();
  //         return;
  //       }
  //     }
  //     while (client.available())
  //     {
  //       String line = client.readStringUntil('\r');
  //       Serial.print(line);
  //     }
  //     Serial.println();
  //     Serial.println("closing connection");
  //     sendRegistrationFlag = false;
  // }
  // server.handleClient();

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

  if(currentTemp >= 32 || currentHumidity >= 40)
  {
    digitalWrite(ventPIN, HIGH);
    ventFlag = true;
    Serial.println("vent is on ");

  }
  if(currentTemp < 32 && currentTemp > 12)
  {
    digitalWrite(ventPIN, LOW);
    ventFlag = false;
    Serial.println("vent is off ");
  }
  if(currentTemp <= 12)
  {
    digitalWrite(blanketPIN, HIGH);
    heatBlanketFlag = true;
    Serial.println("blanket is on");

  }
  if(currentTemp >= 17)
  {
    digitalWrite(blanketPIN, LOW);
    heatBlanketFlag = false;
    Serial.println("blanket is off ");

  }
}

void turnOnBlanket()
{
  digitalWrite(blanketPIN, HIGH);
  heatBlanketFlag = true;
  Serial.println("blanket is on");
}
void turnOffBlanket()
{
  digitalWrite(blanketPIN, LOW);
  heatBlanketFlag = false;
  Serial.println("blanket is off ");
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
