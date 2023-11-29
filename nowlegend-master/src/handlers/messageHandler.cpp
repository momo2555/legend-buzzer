#include "handlers/messageHandler.h"

MessageHandler::MessageHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void MessageHandler::handle(Request *request)
{
    Logger::log("Receive message handler");
    router_->route(request, {});
}

bool MessageHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::DEVICE_DATA ||
           request->getType() == RequestType::DEVICE_EVENT;
}
