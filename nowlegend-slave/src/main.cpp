#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <request.h>
#include <memory>

websockets::WebsocketsClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  const char* ssid {"gogo power ranger"};
  const char* mdp {"momomomo"};
  WiFi.begin(ssid, mdp);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("connected to Wifi");
  
  client.connect("http://172.22.27.198:2225");
  Serial.println("Send message");
  auto request = std::make_unique<Request>();
  Serial.println("phase 0");
  request->asEvent("test");
  request->setDeviceName("buzzer");
  request->setSender(Entity::DEVICE);
  request->setReceiver(Entity::MONITOR);
  auto mac = std::string(WiFi.macAddress().c_str());
  
  request->setMacAddress(mac);
  Serial.println("phase 1");
  Serial.println(request->toString().c_str());
  Serial.println("phase 2");

  client.send(request->toString().c_str());
  
}

void loop() {
  client.poll();
}
