#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
const char* ssid = "wisecareWWIFI";
const char* password = "123456789";
const char* host = "192.168.42.10";
ESP8266WebServer server(80);
String myIP;
String myDevice = "water";
//////////// ----------------- Function Declaration ----------------- ////////////
void TurnOn();
void TurnOff();
String checkFlowtingSwitch();
String getDistance();
void setIpConfiguration();

//////////// ----------------- PINS Configuration ----------------- ////////////
const int levelPin = 14;      // the number of the pushbutton pin ( D5 )
const int levelPin2 = 12;     // the number of the pushbutton pin ( D6 )
const int trigPin = 2;      // D4
const int echoPin = 0;      // D3
const int solenoidPin = 5;  //D8
//////////// ----------------- pins used ----------------- ////////////
// 2,0(D4 green,D3 yellow) -> Distance sensor  |  14,12(D5,D6) -> floating switch | 5(d1) -> solonoid
//////////// ----------------- Variables ----------------- ////////////
String statusResponse="";
long duration;
int distance;
int perecentResponse = -1; // when -1 represent a problem
String _distance="";
bool solenoidActive = false;

void setup()
{
  Serial.begin(115200);
  delay(10);
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

  pinMode(levelPin, INPUT);
  pinMode(levelPin2, INPUT);
  pinMode(solenoidPin,OUTPUT);

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
    server.on("/waterTankAmount", []()
    {
      _distance = getDistance();
      Serial.println(_distance);
      server.send(200, "text/html", _distance);
    });
    server.on("/fillWaterCommand", []()
    {
      TurnOn();
      checkFlowtingSwitch();
      Serial.println(statusResponse);
      server.send(200, "text/html", statusResponse);
    });
    server.begin();

}
bool sendRegistrationFlag = true;
void loop()
{
  if(sendRegistrationFlag)
  {
    setIpConfiguration();
  }
  server.handleClient();
  int TOPswitchState = digitalRead(levelPin);
  if(TOPswitchState == LOW && solenoidActive == true)
  {
    TurnOff();
  }
}

String checkFlowtingSwitch()
{
  int TOPswitchState = digitalRead(levelPin);
  int BOTTOMswitchState = digitalRead(levelPin2);

      if (TOPswitchState == LOW)
      {
         Serial.println ("TOP switch - water above sensor");
         Serial.println ("Water tank full - Solenoid turn off");
         TurnOff();
         return "FULL";
      }
       else
      {
        if (BOTTOMswitchState == HIGH)
        {
           Serial.println ("Water tank empty - Solenoid turn on");
           Serial.println ("Solenoid turn on");
           TurnOn();
           return "EMPTY";
        }
        else
        {
          Serial.println ("water below TOP switch and above BOTTOM switch");
          return "MIDDLE";
        }
      }
}
void TurnOn()
{
  Serial.println("solenoid ON");
  //TOPswitchState = digitalRead(levelPin);
  digitalWrite(solenoidPin, HIGH);
  solenoidActive = true;
}

void TurnOff()
{
  digitalWrite(solenoidPin, LOW);
  solenoidActive = false;
  //Serial.println("solenoid OFF");
}
String getDistance()
{
  pinMode(trigPin, OUTPUT);        // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);         // Sets the echoPin as an Input
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;    // distance by cm
  perecentResponse = 120-((distance*100)/18);     // 18cm = food tank height
  if (perecentResponse <= 20)
  {
    perecentResponse = 1;
  }
  Serial.print ("distance = ");
  Serial.println (distance);
  return(String(perecentResponse));
}

void setIpConfiguration()
{
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 8081;
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
