// //////////// ----------------- Include Libraries ----------------- ////////////
// #include <Arduino.h>
// #include <ESP8266WebServer.h>
// #include "RestClient.h"
// //////////// ----------------- PINS MAP ----------------- ////////////
// // 16 - D0 | 15 - D8 | 14 - D5 | 13 - D7 | 12 - D6 | 5 - D1 | 4 - D2 | 3 - D9 | 2 - D4 | 1 - D10 | 0 - D3
// //////////// ----------------- Connection Configuration ----------------- ////////////
// // const char* ssid = "HOTBOX";
// // const char* password = "0509241127";
// // RestClient client = RestClient("192.168.1.15",3000);
// const char* ssid = "Shenkar-New";
// const char* password = "Shenkarwifi";
// RestClient client = RestClient("172.31.129.30",3000);
//
// ESP8266WebServer server(80);
// //////////// ----------------- Function Declaration ----------------- ////////////
// void TurnOn();
// void TurnOff();
// String checkFlowtingSwitch();
// String getDistance();
// //////////// ----------------- PINS Configuration ----------------- ////////////
// const int levelPin = 14;      // the number of the pushbutton pin ( D5 )
// const int levelPin2 = 12;     // the number of the pushbutton pin ( D6 )
//
// const int trigPin = 2;      // D4
// const int echoPin = 0;      // D3
//
// const int solenoidPin = 5;  //D8
// //////////// ----------------- pins used ----------------- ////////////
// // 2,0(D4 green,D3 yellow) -> Distance sensor  |  14,12(D5,D6) -> floating switch | 5(d1) -> solonoid
// //////////// ----------------- Variables ----------------- ////////////
// String statusResponse="";
// long duration;
// int distance;
// int perecentResponse = -1; // when -1 represent a problem
// String _distance="";
// bool solenoidActive = false;
//
// void setup()
// {
//     pinMode(levelPin, INPUT);
//     pinMode(levelPin2, INPUT);
//     pinMode(solenoidPin,OUTPUT);
//     Serial.begin(115200);
//     Serial.println("connect to WiFi network");
//     client.begin(ssid, password);
//       //////////// ----------------- Routes ----------------- ////////////
//       server.on("/waterStatus", []()
//       {
//         Serial.println("waterStatus");
//         statusResponse = checkFlowtingSwitch();
//         Serial.println(statusResponse);
//         server.send(200, "text/html", statusResponse);
//       });
//       server.on("/waterTankAmount", []()
//       {
//         _distance = getDistance();
//         Serial.println(_distance);
//         server.send(200, "text/html", _distance);
//       });
//       server.on("/fillWaterCommand", []()
//       {
//         TurnOn();
//         checkFlowtingSwitch();
//         Serial.println(statusResponse);
//         server.send(200, "text/html", statusResponse);
//       });
//       server.begin();
// }
// void loop()
// {
//   server.handleClient();
//   int TOPswitchState = digitalRead(levelPin);
//   if(TOPswitchState == LOW && solenoidActive == true)
//   {
//     TurnOff();
//   }
// }
//
// String checkFlowtingSwitch()
// {
//   int TOPswitchState = digitalRead(levelPin);
//   int BOTTOMswitchState = digitalRead(levelPin2);
//
//       if (TOPswitchState == LOW)
//       {
//          Serial.println ("TOP switch - water above sensor");
//          Serial.println ("Water tank full - Solenoid turn off");
//          TurnOff();
//          return "FULL";
//       }
//        else
//       {
//         if (BOTTOMswitchState == HIGH)
//         {
//            Serial.println ("Water tank empty - Solenoid turn on");
//            Serial.println ("Solenoid turn on");
//            TurnOn();
//            return "EMPTY";
//         }
//         else
//         {
//           Serial.println ("water below TOP switch and above BOTTOM switch");
//           return "MIDDLE";
//         }
//       }
// }
// void TurnOn()
// {
//   Serial.println("solenoid ON");
//   int TOPswitchState = digitalRead(levelPin);
//   digitalWrite(solenoidPin, HIGH);
//   solenoidActive = true;
// }
//
// void TurnOff()
// {
//   digitalWrite(solenoidPin, LOW);
//   solenoidActive = false;
//   //Serial.println("solenoid OFF");
// }
// String getDistance()
// {
//   pinMode(trigPin, OUTPUT);        // Sets the trigPin as an Output
//   pinMode(echoPin, INPUT);         // Sets the echoPin as an Input
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   duration = pulseIn(echoPin, HIGH);
//   distance = duration*0.034/2;    // distance by cm
//   perecentResponse = 120-((distance*100)/18);     // 18cm = food tank height
//   if (perecentResponse <= 20)
//   {
//     perecentResponse = 1;
//   }
//   Serial.print ("distance = ");
//   Serial.println (distance);
//   return(String(perecentResponse));
// }
