#include "baseHandler.h"

BaseHandler::BaseHandler(std::shared_ptr<RouterInterface> router)
{
    this->router_ = router;
}

/*void BaseHandler::handle(Request *request)
{

}

bool BaseHandler::canHandle(Request *request)
{
    Serial.println("BaseHandler : canHandle");
    return false;
}*/
