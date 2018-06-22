#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
const char* ssid = "wcnetwork";
const char* password = "wcnetwork";
const char* host = "192.168.4.1";

ESP8266WebServer server(80);
String myIP;
String myDevice = "water";
//////////// ----------------- Fuaction Declaration ----------------- ////////////
void TurnOn();
void TurnOff();
String checkFlowtingSwitch();
String getDistance();
void setIpConfiguration();
String checkAndFillFlowtingSwitch();

//////////// ----------------- PINS Configuration ----------------- ////////////
const int levelPin = 12;      // the number of the pushbutton pin ( D6 )
const int solenoidPin = 0;  //D3
//////////// ----------------- Variables ----------------- ////////////
String statusResponse="";
String floatStatus = "";
bool solenoidActive = false;
int TOPswitchState;
void setup()
{
  Serial.begin(115200);
  pinMode(levelPin, INPUT);
  pinMode(solenoidPin,OUTPUT);
  digitalWrite(solenoidPin, LOW);
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
  TOPswitchState = digitalRead(levelPin);

  Serial.println("connect to WiFi network");
  if (MDNS.begin("esp8266"))
  {
   Serial.println("MDNS responder started");
  }
  //////////// ----------------- Routes ----------------- ////////////
    server.on("/waterStatus", []()
    {
      Serial.println("waterStatus");
      statusResponse = checkFlowtingSwitch();
      Serial.println(statusResponse);
      server.send(200, "text/html", statusResponse);
    });
    server.on("/fillWaterCommand", []()
    {
      //TurnOn();
      statusResponse = checkAndFillFlowtingSwitch();
      Serial.println(statusResponse);
      server.send(200, "text/html", statusResponse);
    });
      server.on("/healthCheck", []()
      {
        Serial.println("healthCheck");
        server.send(200, "text/html", "healthCheckOK");
      });
      server.begin();
      Serial.println("Server begun");
  }
bool sendRegistrationFlag = true;
void loop()
{
  if(sendRegistrationFlag)
  {
    setIpConfiguration();
  }
  server.handleClient();
  TOPswitchState = digitalRead(levelPin);

 floatStatus = checkFlowtingSwitch();
 delay(400);
  if(floatStatus == "FULL" && solenoidActive == true)
  {
    TurnOff();
  }
}

String checkFlowtingSwitch()
{
  int switchState = digitalRead(levelPin);
      if (switchState == LOW)
      {
         return "FULL";
      }
       else
      {
         return "EMPTY";
      }
}
String checkAndFillFlowtingSwitch()
{
  int switchState = digitalRead(levelPin);
      if (switchState == LOW)
      {
         Serial.println ("TOP switch - water above sensor");
         Serial.println ("Water tank full - Solenoid turn off");
         TurnOff();
         return "FULL";
      }
       else
      {
           Serial.println ("Water tank empty - Solenoid turn on");
           Serial.println ("Solenoid turn on");
           TurnOn();
           return "EMPTY";
      }
}
void TurnOn()
{
  Serial.println("solenoid ON");
  solenoidActive = true;
  digitalWrite(solenoidPin, HIGH);
}

void TurnOff()
{
  digitalWrite(solenoidPin, LOW);
  solenoidActive = false;
  Serial.println("solenoid OFF");
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
