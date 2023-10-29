#include "handlers/heartbeatHandler.h"

HeartbeatHandler::HeartbeatHandler(std::shared_ptr<RouterInterface> router)
    : BaseHandler {router}
{

}

void HeartbeatHandler::handle(Request *request)
{
}

bool HeartbeatHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::HEARTBEAT;
}
