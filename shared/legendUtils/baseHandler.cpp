#include "baseHandler.h"

BaseHandler::BaseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
{
    this->router_ = router;
    this->deviceManager_ = deviceManager;
}

/*void BaseHandler::handle(Request *request)
{

}

bool BaseHandler::canHandle(Request *request)
{
    Serial.println("BaseHandler : canHandle");
    return false;
}*/
