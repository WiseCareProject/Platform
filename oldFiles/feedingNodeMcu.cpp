// //////////// ----------------- Include Libraries ----------------- ////////////
// #include <Arduino.h>
// #include "HX711.h"
// #include <hcsr04.h>
// #include <ESP8266WebServer.h>
// #include "RestClient.h"
// #include <Servo.h>
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
// float myScale();
// void OperateServo();
// float currentAmount;
// #define calibration_factor 453.6
// //////////// ----------------- PINS Configuration ----------------- ////////////
// #define TRIG_PIN 14
// #define ECHO_PIN 12
// const int servoAttach = 15;
// //////////// ----------------- pins used ----------------- ////////////
// // 12,13(D3,D4) -> Distance sensor  |  15(d8) - servo |  5,16(D1-y, D0-w) -> scale
// //////////// ----------------- Variables ----------------- ////////////
// long duration;
// int distance;
// String _distance;
// Servo myservo;  // create servo object to control a servo
// HX711 plateScale(D1, D0);
// bool servoFlag = false;
// int requiredAmount;
// void setup()
// {
//   myservo.attach(servoAttach);
//   myservo.write(90);
//   HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000); // TRIG_PIN , ECHO_PIN ,20,4000
//   Serial.begin(115200);
//   plateScale.set_scale(calibration_factor);
//   plateScale.tare();
//   Serial.println("connect to WiFi network");
//   client.begin(ssid, password);
//   //////////// ----------------- Routes ----------------- ////////////
//   server.on("/feed", []()
//   {
//     requiredAmount = server.arg(0).toInt();
//
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
//   server.handleClient();
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
//   while(_currentAmount < requiredAmount-10)
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
//   int perecentResponse = 120-((distance*100)/20);     // 20cm = food tank height
//   return(String(perecentResponse));
// }
