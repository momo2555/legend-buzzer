#include "handlers/echoHandler.h"

EchoHandler::EchoHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void EchoHandler::handle(Request *request)
{
    Serial.println("EchoHandler : receive echo - send it back ");
    auto echoResponseReq = std::make_unique<Request>(Request());
    echoResponseReq->asEchoResponse();
    MacAddress myAddress{};
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
    MacAddress sender = request->getSenderAddress();
    //com_->sendOnce(sender, echoResponseReq.get(), true);
    echoResponseReq->setSender(Entity::MASTER, myAddress);
    echoResponseReq->setReceiver(Entity::DEVICE, sender);

    this->deviceManager_->addNewDevice(sender);
    this->router_->route(echoResponseReq.get(), sender);
}

bool EchoHandler::canHandle(Request *request)
{
    Serial.println("EchoHandler : Is it an echo request ?");
    return request->getType() == RequestType::ECHO;
    
}
