#include <Arduino.h>
#include <WiFi.h>
#include <request.h>
#include <memory>
#include <legend.h>

std::unique_ptr<Legend> legend {};

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  // const char* ssid {"gogo power ranger"};
  // const char* mdp {"momomomo"};
  
  
  // Logger::log("Send message");
  // auto request = std::make_unique<Request>();
  // Logger::log("phase 0");
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
  // Logger::log("phase 1");
  // Logger::log(request->toString().c_str());
  // Logger::log("phase 2");
  // Logger::log(request->toString().length());
  // RequestBody req = request->getRequestBody();
  // Logger::log(req.data.size());
  // Logger::log(sizeof(req));

  legend =  std::make_unique<Legend>(Legend());
  legend->run();

  
  
  
}

void loop() {
  if (legend->isReady()) {
    delay(5000);
    // create a new request
    Logger::log("FRAME 1 ---");
    Request request {};
    request.asData();
    request.setData<int>("test", 45);
    request.setData<float>("test2", 45.5);
    request.setData<bool>("test3", false);
    request.setReceiver(Entity::MONITOR, {});
    request.setSender(Entity::DEVICE, MacAddress("AD:AD:AD:AD:AD:AD"));
    Logger::log(request.toString());

    Logger::log("FRAME 2 ---");
    //Request request {std::string("\"header\"")};
    
    legend->sendRequest(request, Entity::MONITOR);
    Logger::log("I'm ready - send event");
    
  }
  
}
