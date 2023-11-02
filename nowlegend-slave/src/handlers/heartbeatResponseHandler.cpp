#include "handlers/heartbeatResponseHandler.h"

HeartbeatResponseHandler::HeartbeatResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void HeartbeatResponseHandler::handle(Request *request)
{
   
}

bool HeartbeatResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::HEARTBEAT_RESPONSE;
    
}
