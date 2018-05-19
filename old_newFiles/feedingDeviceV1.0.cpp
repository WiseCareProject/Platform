// //////////// ----------------- Include Libraries ----------------- ////////////
// #include <Arduino.h>
// #include "HX711.h"
// #include <hcsr04.h>
// #include <ESP8266WebServer.h>
// #include "RestClient.h"
// #include <Servo.h>
//
// //////////// ----------------- PINS MAP ----------------- ////////////
// // 16 - D0 | 15 - D8 | 14 - D5 | 13 - D7 | 12 - D6 | 5 - D1 | 4 - D2 | 3 - D9 | 2 - D4 | 1 - D10 | 0 - D3
// //////////// ----------------- Connection Configuration ----------------- ////////////
// const char* ssid = "HOTBOX";
// const char* password = "0509241127";
// RestClient client = RestClient("192.168.1.15",3000);
// ESP8266WebServer server(80);
// //////////// ----------------- Function Declaration ----------------- ////////////
// String getDistance();
// float myScale();
// void OperateServo();
// float currentAmount;
// #define calibration_factor 453.6
// //////////// ----------------- PINS Configuration ----------------- ////////////
// const int trigPin = 2;      // D4
// const int echoPin = 0;      // D3
// const int servoAttach = 13;
// //////////// ----------------- pins used ----------------- ////////////
// // 0,2(D3,D4) -> Distance sensor  |  13(d7) - servo |  5,16(D1-y, D0-w) -> scale
// //////////// ----------------- Variables ----------------- ////////////
// long duration;
// int distance;
// String _distance;
// int perecentResponse = -1; // when -1 represent a problem
//
// Servo myservo;  // create servo object to control a servo
// HX711 plateScale(D1, D0);
// bool servoFlag = false;
// int requiredAmount;
// void setup()
// {
//   myservo.attach(servoAttach);
//   myservo.write(90);
//   Serial.begin(115200);
//   plateScale.set_scale(calibration_factor);
//   plateScale.tare();
//   Serial.println("connect to WiFi network");
//   client.begin(ssid, password);
//   //////////// ----------------- Routes ----------------- ////////////
//   server.on("/feed", []()
//   {
//     requiredAmount = server.arg(0).toInt();
//     Serial.println("feed me!!!!");
//     OperateServo();
//     if(servoFlag)
//     {
//       currentAmount = myScale();
//       server.send(200, "text/html", String(currentAmount));
//       servoFlag = false;
//     }
//   });
//   server.on("/scale", []()
//   {
//     Serial.println("scale");
//     Serial.println(server.arg(0));
//     currentAmount = myScale();
//     server.send(200, "text/html", String(currentAmount));
//   });
//   server.on("/tankAmount", []()
//   {
//     _distance = getDistance();
//     Serial.println(_distance);
//     server.send(200, "text/html", _distance);
//   });
// server.begin();
// }
// void loop()
// {
//  server.handleClient();
// }
// float myScale()
// {
//   plateScale.power_up();
//   Serial.println("");
//   Serial.println("===================================");
//   Serial.println(plateScale.get_units());
//   Serial.println("===================================");
//   String response = "";
//   float plateAmount_data = plateScale.get_units();
//   Serial.println(response);
//   plateScale.power_down();
//   return plateAmount_data;
// }
// void OperateServo()
// {
//   float _currentAmount = myScale();
//
//   Serial.println("Get in servo: ");
//   while(_currentAmount < requiredAmount-20)
//   {
//     myservo.write(180);
//     _currentAmount = myScale();
//     delay(1000);
//     Serial.println("");
//     Serial.print("Current Amount = ");
//     Serial.println(_currentAmount);
//   }
//    myservo.write(90);
//    servoFlag = true;
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
