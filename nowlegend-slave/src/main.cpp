#include <Arduino.h>
#include <WiFi.h>
#include <request.h>
#include <memory>
#include <legend.h>

std::unique_ptr<Legend> legend {};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // const char* ssid {"gogo power ranger"};
  // const char* mdp {"momomomo"};
  
  
  // Serial.println("Send message");
  // auto request = std::make_unique<Request>();
  // Serial.println("phase 0");
  // request->asEvent("test");
  // request->setDeviceName("buzzer");
  // request->setSender(Entity::DEVICE);
  // request->setReceiver(Entity::MONITOR);
  // //request->setMacAddress(WiFi.macAddress().c_str());

  // request->asData();
  // request->setData<float>("imuac1", 12.9f);
  // request->setData<int>("imuac2", 5);
  // request->setData<float>("imuac3", 12.9f);
  // request->setData<float>("imuac4", 12.9f);
  // Serial.println("phase 1");
  // Serial.println(request->toString().c_str());
  // Serial.println("phase 2");
  // Serial.println(request->toString().length());
  // RequestBody req = request->getRequestBody();
  // Serial.println(req.data.size());
  // Serial.println(sizeof(req));

  legend =  std::make_unique<Legend>(Legend());
  legend->run();

  
  
  
}

void loop() {
  if (legend->isReady()) {
    delay(5000);
    // create a new request
    Request request {};
    request.asEvent("coucou");
    legend->sendRequest(request, Entity::MONITOR);
    Serial.println("I'm ready - send event");
    
  }
  
}
