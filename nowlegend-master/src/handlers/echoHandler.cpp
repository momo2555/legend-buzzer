#include "handlers/echoHandler.h"

EchoHandler::EchoHandler(std::shared_ptr<RouterInterface> router)
    : BaseHandler {router}
{

}

void EchoHandler::handle(Request *request)
{
    Serial.println("receive echo - send it back ");
    auto echoResponseReq = std::make_unique<Request>(Request());
    echoResponseReq->asEchoResponse();
    MacAddress myAddress{};
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
    echoResponseReq->setMacAddress(myAddress);

    MacAddress sender = request->getMacAddress();
    //com_->sendOnce(sender, echoResponseReq.get(), true);
    this->router_->route(request, sender);
}

bool EchoHandler::canHandle(Request *request)
{
    Serial.println("It's an echo request");
    return request->getType() == RequestType::ECHO;
    
}
