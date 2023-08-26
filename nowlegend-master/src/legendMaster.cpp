#include "legendMaster.h"

LegendMaster::LegendMaster() {
    com_ = std::make_unique<Transmission>(Transmission());
    com_->initTransmission();
}
void LegendMaster::run() {
    com_->OnDataRecv<LegendMaster>(this, &LegendMaster::dataRecvCallback_);


}

void LegendMaster::dataRecvCallback_(const unsigned char *addr, const unsigned char *data, int size)
{
    Serial.println("receive data");
    auto receivedRequest = std::make_unique<Request>(Request(data, size));
    switch (receivedRequest->getType())
    {
    case RequestType::ECHO: // STEP 1
        // send bach the echo
        Serial.println("receive echo ");
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
    }
}

void LegendMaster::sendEchoResponseFrame_ () {
    // broadcast an echo message
    auto echoReq = std::make_unique<Request>(Request());
    echoReq->asEchoResponse();
    MacAddress myAddress{};
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
    echoReq->setMacAddress(myAddress);
    MacAddress emptyAddr {};
    com_->send(emptyAddr, echoReq.get(), SendMethod::BROADCAST);
    
}