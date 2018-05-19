// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>
// #include <Arduino.h>
// #include "HX711.h"
// #include <hcsr04.h>
// #include <Servo.h>
//
// const char* ssid = "wisecare-WIFI";
// const char* password = "123456789";
// const char* host = "192.168.42.10";
// ESP8266WebServer server(80);
//
// String myIP;
// String myDevice = "food";
//
// //////////// ----------------- Function Declaration ----------------- ////////////
// String getDistance();
// void resetScale();
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
//
// void setup()
// {
//   Serial.begin(115200);
//   delay(10);
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
//
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP().toString());
//   myIP = WiFi.localIP().toString();
//
//   myservo.attach(servoAttach);
//   myservo.write(90);
//   plateScale.set_scale(calibration_factor);
//   plateScale.tare();
//   Serial.println("connect to WiFi network");
//   if (MDNS.begin("esp8266"))
//   {
//    Serial.println("MDNS responder started");
//   }
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
//   server.on("/cleanScale", []()
//   {
//     Serial.println("clean scale");
//     resetScale();
//     server.send(200, "text/html", "scaleCleand");
//   });
//   server.on("/tankAmount", []()
//   {
//     _distance = getDistance();
//     Serial.println(_distance);
//     server.send(200, "text/html", _distance);
//   });
//   server.begin();
//   Serial.println("Server begun");
// }
// bool sendRegistrationFlag = true;
// void loop()
// {
//   server.handleClient();
//   if(sendRegistrationFlag)
//     {
//       Serial.print("connecting to ");
//       Serial.println(host);
//       WiFiClient client;
//       const int httpPort = 8081;
//       if (!client.connect(host, httpPort))
//       {
//         Serial.println("connection failed");
//         return;
//       }
//       Serial.print("Requesting URL: ");
//       Serial.println(host);
//       client.print(String("GET ") + "/register?ip="+ myIP +"&device=" + myDevice + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" +"Connection: close\r\n\r\n");
//       unsigned long timeout = millis();
//       while (client.available() == 0)
//       {
//         if (millis() - timeout > 5000)
//         {
//           Serial.println(">>> Client Timeout !");
//           client.stop();
//           return;
//         }
//       }
//       while (client.available())
//       {
//         String line = client.readStringUntil('\r');
//         Serial.print(line);
//         server.handleClient();
//       }
//       Serial.println();
//       Serial.println("closing connection");
//       sendRegistrationFlag = false;
//   }
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
// void resetScale()
// {
//   plateScale.tare();
// }
