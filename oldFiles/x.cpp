// //////////// ----------------- Include Libraries ----------------- ////////////
// #include <Arduino.h>
// #include <hcsr04.h>
// #include <ESP8266WebServer.h>
// #include "RestClient.h"
// // const char* ssid = "Shenkar-New";
// // const char* password = "Shenkarwifi";
// const char* ssid = "HOTBOX";
// const char* password = "0509241127";
// // const char* ssid = "SafechargeGuests";
// // const char* password = "welcome!";
//
// #define TRIG_PIN 12
// #define ECHO_PIN 13
// HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
//
// RestClient client = RestClient("172.31.129.30",3000);
// long duration;
// int distance;
// String getDistance();
// float currentAmount;
// void TurnOn();
// void TurnOff();
// void checkFlowtingSwitch();
// //////////// ----------------- PINS Configuration ----------------- ////////////
// const int trigPin = 0;  // D3
// const int echoPin = 2;  // D4
// //////////// ----------------- pins used ----------------- ////////////
// // 0,2(D3green,D4) -> Distance sensor  |  12,14(D6,D5) -> floating switch | 4(d2) -> solonoid
// //////////// ----------------- Variables ----------------- ////////////
// String _distance="";
// String statusResponse="";
// const int topSwitchPin = 14;    // ( D8 )
// const int bottomSwitchPin = 12; // ( D0 )
// const int solenoidPin = 4;
//
// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("connect to WiFi network");
//     client.begin(ssid, password);
// }
// void loop()
// {
//   String test = getDistance();
//   Serial.print("Tank Amnout By Perecent = ");
//   Serial.println(test);
//   //checkFlowtingSwitch();
//
//   delay(2000);
// }
// String getDistance()
// {
//   pinMode(TRIG_PIN, OUTPUT);        // Sets the trigPin as an Output
//   pinMode(ECHO_PIN, INPUT);         // Sets the echoPin as an Input
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);
//   duration = pulseIn(ECHO_PIN, HIGH);
//   distance = duration*0.034/2;       // distance by cm
//   Serial.print("distance by cm = ");
//   Serial.println(distance);
//   int perecentResponse = 120-((distance*100)/18);     // 20cm = food tank height
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
