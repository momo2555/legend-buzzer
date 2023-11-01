#include "handlers/heartbeatHandler.h"

HeartbeatHandler::HeartbeatHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void HeartbeatHandler::handle(Request *request)
{
}

bool HeartbeatHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::HEARTBEAT;
}
