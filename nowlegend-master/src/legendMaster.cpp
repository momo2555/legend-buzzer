#include "legendMaster.h"

LegendMaster::LegendMaster() {
    this->com_ = std::make_shared<Transmission>(Transmission());
    this->com_->initTransmission();
    router_ = std::make_shared<RouterInterface>(RouterInterface(com_));
    handlerManager_ = std::make_unique<HandlerManager>(HandlerManager(router_));
    //echo Handler
    auto echoHandler = EchoHandler(router_);
    auto messageHandler = MessageHandler(router_);
    auto identificationHandler = IdentificationHandler(router_);
    auto heartbeatHandler = HeartbeatHandler(router_);

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
    
    /*switch (receivedRequest->getType())
    {
    case RequestType::ECHO: // STEP 1
        // send back the echo

        this->sendEchoResponseFrame_(receivedRequest.get());
        break;
    case RequestType::IDENTIFICATION: // STEP 2
        // The master confirm the identification
        break;
    case RequestType::DEVICE_DATA:
        // Receive new data
        break;
    case RequestType::DEVICE_EVENT:
        // receive a new event
        break;
    default:
        break;
    }*/
}

/*void LegendMaster::sendEchoResponseFrame_ (Request* echoRequest) {
    // broadcast an echo message
    auto echoResponseReq = std::make_unique<Request>(Request());
    echoResponseReq->asEchoResponse();
    MacAddress myAddress{};
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
    echoResponseReq->setMacAddress(myAddress);

    MacAddress sender = echoRequest->getMacAddress();
    com_->sendOnce(sender, echoResponseReq.get(), true);
    
}*/