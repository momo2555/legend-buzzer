#include <Arduino.h>
#include <WiFi.h>
#include <request.h>
#include <memory>



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  const char* ssid {"gogo power ranger"};
  const char* mdp {"momomomo"};
  
  
  Serial.println("Send message");
  auto request = std::make_unique<Request>();
  Serial.println("phase 0");
  request->asEvent("test");
  request->setDeviceName("buzzer");
  request->setSender(Entity::DEVICE);
  request->setReceiver(Entity::MONITOR);
  request->setMacAddress(WiFi.macAddress().c_str());

  request->asData();
  request->setData("imuaccel1", 12.9f);
  request->setData("imuaccel2", 12.9f);
  request->setData("imuaccel3", 12.9f);
  Serial.println("phase 1");
  Serial.println(request->toString().c_str());
  Serial.println("phase 2");
  Serial.println(request->toString().length());
  RequestBody req = request->getRequestBody();
  Serial.println(req.data.size());
  Serial.println(sizeof(req));
  
  
}

void loop() {
  
}
