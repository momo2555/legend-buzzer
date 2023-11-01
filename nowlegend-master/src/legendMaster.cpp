#include "legendMaster.h"

LegendMaster::LegendMaster() {
    this->com_ = std::make_shared<Transmission>(Transmission());
    this->com_->initTransmission();

    router_ = std::make_shared<RouterInterface>(RouterInterface(com_));
    deviceManager_ = std::make_shared<DeviceManager>(DeviceManager());
    handlerManager_ = std::make_unique<HandlerManager>(HandlerManager(router_));
    //Handlers
    auto echoHandler = new EchoHandler(router_, deviceManager_);
    auto messageHandler = new MessageHandler(router_, deviceManager_);
    auto identificationHandler = new IdentificationHandler(router_, deviceManager_);
    auto heartbeatHandler = new HeartbeatHandler(router_, deviceManager_);

    handlerManager_->addHandler(echoHandler);
    handlerManager_->addHandler(messageHandler);
    handlerManager_->addHandler(identificationHandler);
    handlerManager_->addHandler(heartbeatHandler);

}

void LegendMaster::run() {
    com_->OnDataRecv<LegendMaster>(this, &LegendMaster::dataRecvCallback_);
}

void LegendMaster::dataRecvCallback_(const unsigned char *addr, const unsigned char *data, int size)
{
    Serial.println("receive data");
    auto receivedRequest = std::make_unique<Request>(Request(data, size));
    this->handlerManager_->handleRequest(receivedRequest.get());
}