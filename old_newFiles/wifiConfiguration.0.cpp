// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
//
// const char* ssid = "wisecare-WIFI";
// const char* password = "123456789";
// const char* host = "192.168.42.10";
// ESP8266WebServer server(80);
//
// String myIP;
// String myDevice = "food";
// void setup()
// {
//   Serial.begin(115200);
//   delay(10);
//
//   Serial.println();
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
//   Serial.println(WiFi.localIP());
//   myIP = WiFi.localIP().toString();
//
//     server.on("/test", []()
//     {
//       Serial.println("test me!!!!");
//     });
//     server.begin();
// }
// bool sendRegistrationFlag = true;
// void loop()
// {
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
//       }
//       Serial.println();
//       Serial.println("closing connection");
//   }
//   sendRegistrationFlag = false;
//   server.handleClient();
// }
