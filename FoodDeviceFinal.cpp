#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include "HX711.h"
#include <Servo.h>
#include <Ultrasonic.h>
#define calibration_factor 453.6

//////////// ----------------- Connection details ----------------- ////////////
const char* ssid = "wcnetwork";
const char* password = "wcnetwork";
const char* host = "192.168.4.1";
ESP8266WebServer server(80);
String myIP;
String myDevice = "food";
//////////// ----------------- Function Declaration ----------------- ////////////
float getDistance();
float distanceFloatingAverage(int);
float getDistanceByPerecentage(int);
void stopServo();
float myScale();
void OperateServo();
void setIpConfiguration();
float currentAmount;
//////////// ----------------- PINS Configuration ----------------- ////////////
const int servoAttach = 14;  //d5
Ultrasonic ultrasonic1(13, 15);	// trig d7,echo d8
HX711 plateScale(D1, D0);
Servo myservo;            // create servo object to control a servo
String _distance;
int perecentResponse = -1; // when -1 represent a problem
bool servoFlag = false;
int requiredAmount;
bool sendRegistrationFlag = true;

//////////// ----------------- pins used ----------------- ////////////
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
  Serial.println(WiFi.localIP().toString());
  myIP = WiFi.localIP().toString();

  myservo.attach(servoAttach);
  myservo.write(90);
  plateScale.set_scale(calibration_factor);
  plateScale.tare();
  Serial.println("connect to WiFi network");
  if (MDNS.begin("esp8266"))
  {
   Serial.println("MDNS responder started");
  }
  //////////// ----------------- Routes ----------------- ////////////
  server.on("/feed", []()
  {
    requiredAmount = server.arg(0).toInt();
    Serial.println("feed me!!!!");
    OperateServo();
    if(servoFlag)
    {
      currentAmount = myScale();
      server.send(200, "text/html", String(currentAmount));
      servoFlag = false;
    }
  });
  server.on("/scale", []()
  {
    Serial.println("scale");
    //Serial.println(server.arg(0));
    currentAmount = myScale();
    server.send(200, "text/html", String(currentAmount));
  });
  server.on("/stopServo", []()
  {
    Serial.println("stopServo");
    stopServo();
    server.send(200, "text/html", "servoStopped");
  });
  server.on("/tankAmount", []()
  {
    _distance = getDistanceByPerecentage(19);
    Serial.println(_distance);
    server.send(200, "text/html", _distance);
  });
  server.on("/healthCheck", []()
  {
    Serial.println("healthCheck");
    server.send(200, "text/html", "healthCheckOK");
  });
  server.begin();
  Serial.println("Server begun");
 }

void loop()
{
  server.handleClient();
  if(sendRegistrationFlag)
   {
     setIpConfiguration();
  }
}
///////////// -------------- Scale -------------- ///////////////
float myScale()
{
  plateScale.power_up();
  Serial.println("");
  Serial.println("===================================");
  Serial.println(plateScale.get_units());
  Serial.println("===================================");
  String response = "";
  float plateAmount_data = plateScale.get_units();
  Serial.println(response);
  plateScale.power_down();
  return plateAmount_data;
}
/////////////// -------------- Servo -------------- ///////////////
void OperateServo()
{
  float _currentAmount = myScale();

  Serial.println("Get in servo: ");
  while(_currentAmount < requiredAmount-20)
  {
    myservo.write(180);
    _currentAmount = myScale();
    delay(1000);
    Serial.println("");
    Serial.print("Current Amount = ");
    Serial.println(_currentAmount);
  }
   myservo.write(90);
   servoFlag = true;
}
void stopServo()
{
  myservo.write(90);
}
/////////////// -------------- IP Configuration -------------- ///////////////
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
/////////////// -------------- UltraSonic -------------- ///////////////
float getDistance()
{
  float tempDistance = ultrasonic1.distanceRead();
  return tempDistance;
}
float distanceFloatingAverage(int numOfChecks)
{
  float result = 0;

  for(int i=0;i<numOfChecks;i++)
  {
    float tmp = getDistance();
    result += tmp;
    delay(200);
  }
  return(result/numOfChecks);
}
float getDistanceByPerecentage(int tankHigh)
{
  Serial.println("");
  float x = distanceFloatingAverage(6);
  Serial.print(x);
  float result = (x*100)/tankHigh;
  float _Result = 120 - result;
  if(_Result < 0 || x >= tankHigh)
  {
    _Result = 0;
  }
  if(_Result > 100 || x <= 5)
  {
    _Result = 100;
  }
  Serial.print(_Result);
  return _Result;
}
