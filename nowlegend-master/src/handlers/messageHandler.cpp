#include "handlers/messageHandler.h"

MessageHandler::MessageHandler(std::shared_ptr<RouterInterface> router)
    : BaseHandler {router}
{

}

void MessageHandler::handle(Request *request)
{

}

bool MessageHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::DEVICE_DATA ||
           request->getType() == RequestType::DEVICE_EVENT;
}
