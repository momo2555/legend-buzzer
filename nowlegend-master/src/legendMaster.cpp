#include "legendMaster.h"

LegendMaster::LegendMaster() {
    this->com_ = std::make_shared<Transmission>(Transmission());
    this->com_->initTransmission();

    this->serial_ = std::make_shared<SerialportInterface>(SerialportInterface());
    this->serial_->init();

    router_ = std::make_shared<Router>(Router(com_, serial_));
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

void LegendMaster::setup()
{
    // check heartbeat of all connected devices
    for(Device device : this->deviceManager_->getAll()) {
        if(device.aliveTimer.isElapsed(3000) && device.state == ConnectionState::CONNECTED) {
            this->deviceManager_->disconnectDevice(device.address);
            Logger::log("Device disconnected mac = " + 
                            device.address.toString());
        }
    }

}

void LegendMaster::dataRecvCallback_(const unsigned char *addr, const unsigned char *data, int size)
{
    Logger::log("receive data");
    auto receivedRequest = std::make_unique<Request>(Request(data, size));
    this->handlerManager_->handleRequest(receivedRequest.get());
    
}