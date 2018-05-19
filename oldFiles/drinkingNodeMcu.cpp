// //////////// ----------------- Include Libraries ----------------- ////////////
// #include <Arduino.h>
// #include <HCSR04.h>
// #include <ESP8266WebServer.h>
// #include "RestClient.h"
// //////////// ----------------- PINS MAP ----------------- ////////////
// // 16 - D0 | 15 - D8 | 14 - D5 | 13 - D7 | 12 - D6 | 5 - D1 | 4 - D2 | 3 - D9 | 2 - D4 | 1 - D10 | 0 - D3
// //////////// ----------------- Connection Configuration ----------------- ////////////
// // const char* ssid = "HOTBOX";
// // const char* password = "0509241127";
// // RestClient client = RestClient("192.168.1.15",3000);
// const char* ssid = "SafechargeGuests";
// const char* password = "welcome!";
// RestClient client = RestClient("172.31.129.30",3000);
// ESP8266WebServer server(80);
// //////////// ----------------- Function Declaration ----------------- ////////////
// String getDistance();
// void TurnOn();
// void TurnOff();
// void checkFlowtingSwitch();
// //////////// ----------------- PINS Configuration ----------------- ////////////
// const int trigPin = 5;  // D4
// const int echoPin = 4;  // D3
// //////////// ----------------- pins used ----------------- ////////////
// // 0,2(D3green,D4) -> Distance sensor  |  12,14(D6,D5) -> floating switch | 4(d2) -> solonoid
// //////////// ----------------- Variables ----------------- ////////////
// long duration;
// int distance;
// String _distance="";
// String statusResponse="";
// const int topSwitchPin = 14;    // ( D5 )
// const int bottomSwitchPin = 12; // ( D6 )
// const int solenoidPin = 4;
// UltraSonicDistanceSensor hcsr04(trigPin, echoPin);
//
// void setup()
// {
//   pinMode(topSwitchPin, INPUT);
//   pinMode(bottomSwitchPin, INPUT);
//   pinMode(solenoidPin,OUTPUT);
//    // TRIG_PIN , ECHO_PIN ,20,4000
//   Serial.begin(115200);
//   Serial.println("connect to WiFi network");
//   client.begin(ssid, password);
//   //////////// ----------------- Routes ----------------- ////////////
//   server.on("/waterStatus", []()
//   {
//     Serial.println("waterStatus");
//     server.send(200, "text/html", statusResponse);
//   });
//   server.on("/waterTankAmount", []()
//   {
//     _distance = getDistance();
//     Serial.println(_distance);
//     server.send(200, "text/html", _distance);
//   });
// server.begin();
// }
// void loop()
// {
//   //checkFlowtingSwitch();
//   server.handleClient();
//  _distance = getDistance();
//   Serial.println(hcsr04.measureDistanceCm());
//
//   delay(3000);
//   // TurnOn();
//   // delay(2000);
//   // TurnOff();
//   // delay(2000);
// }
//
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
//   int perecentResponse = 120-((distance*100)/18);     // 18cm = food tank height
//   Serial.println (distance);
//
//
//
//   return(String(perecentResponse));
// }
// void checkFlowtingSwitch()
// {
//   byte TOPswitchState = digitalRead (topSwitchPin);
//   byte BOTTOMswitchState = digitalRead (bottomSwitchPin);
//       if (TOPswitchState == HIGH)
//       {
//          Serial.println ("TOP switch - water above sensor");
//          Serial.println ("Water tank full - Solenoid turn off");
//          TurnOff();
//          statusResponse="FULL";
//       }
//        else
//       {
//         if (BOTTOMswitchState == LOW)
//         {
//            Serial.println ("Water tank empty - Solenoid turn on");
//            Serial.println ("Solenoid turn on");
//            TurnOn();
//            statusResponse="EMPTY";
//         }
//         else
//         {
//           Serial.println ("water below TOP switch and above BOTTOM switch");
//           statusResponse="MIDDLE";
//         }
//       }
// }
//
// void TurnOn()
// {
//   //digitalWrite(solenoidPin, HIGH);
//   Serial.println("solenoid ON");
// }
// void TurnOff()
// {
//   //digitalWrite(solenoidPin, LOW);
//   Serial.println("solenoid OFF")   ;
// }
