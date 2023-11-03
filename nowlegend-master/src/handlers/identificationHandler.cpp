#include "handlers/identificationHandler.h"

IdentificationHandler::IdentificationHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void IdentificationHandler::handle(Request *request)
{
    Serial.println("Receive identification request");
    auto IdentifyResponseReq = std::make_unique<Request>(Request());
    IdentifyResponseReq->asIdentificationResponse(IdentificationResult::ACCEPTED);
    MacAddress myAddress{};
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
    MacAddress deviceAddr = request->getSenderAddress();
    //com_->sendOnce(sender, echoResponseReq.get(), true);
    IdentifyResponseReq->setSender(Entity::MASTER, myAddress);
    IdentifyResponseReq->setReceiver(Entity::DEVICE, deviceAddr);

    //update device (set as connected)
    if(this->deviceManager_->isDeviceExist(deviceAddr)) {
        Device device = this->deviceManager_->getDevice(deviceAddr);
        device.state = ConnectionState::CONNECTED;
        device.aliveTimer.timer();
        this->deviceManager_->updateDevice(deviceAddr, device);
    }
    this->router_->route(IdentifyResponseReq.get(), deviceAddr);
}

bool IdentificationHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::IDENTIFICATION;
}

