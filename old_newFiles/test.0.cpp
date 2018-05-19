// // //////////// ----------------- Include Libraries ----------------- ////////////
//  #include <Arduino.h>
// // #include <ESP8266WebServer.h>
// // #include "RestClient.h"
// // //////////// ----------------- PINS MAP ----------------- ////////////
// // // 16 - D0 | 15 - D8 | 14 - D5 | 13 - D7 | 12 - D6 | 5 - D1 | 4 - D2 | 3 - D9 | 2 - D4 | 1 - D10 | 0 - D3
// // //////////// ----------------- Connection Configuration ----------------- ////////////
// // // const char* ssid = "HOTBOX";
// // // const char* password = "0509241127";
// // // RestClient client = RestClient("192.168.1.15",3000);
// // const char* ssid = "SafechargeGuests";
// // const char* password = "welcome!";
// // RestClient client = RestClient("172.31.129.30",3000);
// // ESP8266WebServer server(80);
// // String getDistance();
// // //////////// ----------------- Variables ----------------- ////////////
// // String statusResponse="";
// // long duration;
// // int distance;
// // int perecentResponse = -1; // when -1 represent a problem
// // String _distance="";
// //
// // // #define TRIG_PIN 12
// // // #define ECHO_PIN 13
// //
// // #define TRIGGER_PIN  14 // D5
// // #define ECHO_PIN     12 //D6
// //
// // //HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
// //
// // void setup()
// // {
// //     Serial.begin(115200);
// //     Serial.println("connect to WiFi network");
// //     client.begin(ssid, password);
// //     pinMode(TRIGGER_PIN, OUTPUT);
// //     pinMode(ECHO_PIN, INPUT);
// // }
// //
// //
// // void loop()
// // {
// //   digitalWrite(TRIGGER_PIN, LOW);  // Get Start
// //   delayMicroseconds(2); // stable the line
// //   digitalWrite(TRIGGER_PIN, HIGH); // sending 10 us pulse
// //   delayMicroseconds(10); // delay
// //   digitalWrite(TRIGGER_PIN, LOW); // after sending pulse wating to receive signals
// //   duration = pulseIn(ECHO_PIN, HIGH); // calculating time
// //   distance = (duration/2) / 29.1; // single path
// //   Serial.print(distance);
// //   Serial.println(" cm");
// //   delay(100);
// // }
//
//
// // String getDistance()
// // {
// //   pinMode(TRIG_PIN, OUTPUT);        // Sets the trigPin as an Output
// //   pinMode(ECHO_PIN, INPUT);         // Sets the echoPin as an Input
// //   digitalWrite(TRIG_PIN, LOW);
// //   delayMicroseconds(2);
// //   digitalWrite(TRIG_PIN, HIGH);
// //   delayMicroseconds(10);
// //   digitalWrite(TRIG_PIN, LOW);
// //   duration = pulseIn(ECHO_PIN, HIGH);
// //   distance = duration*0.034/2;    // distance by cm
// //   perecentResponse = 120-((distance*100)/18);     // 18cm = food tank height
// //   if (perecentResponse <= 20)
// //   {
// //     perecentResponse = 1;
// //   }
// //   Serial.print ("distance = ");
// //   Serial.println (distance);
// //   return(String(perecentResponse));
// // }
//
// // defines pins numbers
// #define TRIGGERPIN D4
// #define ECHOPIN    D3
// const int trigPin = 2;  //D4
// const int echoPin = 0;  //D3
//
// // defines variables
// long duration;
// int distance;
// void sample_distance();
// void setup()
// {
// pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
// pinMode(echoPin, INPUT); // Sets the echoPin as an Input
// Serial.begin(115200); // Starts the serial communication
// }
//
// void loop() {
// sample_distance();
// //Serial.println("Distance: ");
// //Serial.println(distance);
// delay(2000);
//
// }
//
//
// void sample_distance() {
//
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//
//   duration = pulseIn(echoPin, HIGH);
//   Serial.println(duration);
//   distance = duration*0.034/2;
//   //distance = ((duration / 2) / 29.155);
//   Serial.println("Distance: ");
//   Serial.println(distance);
//
// }
