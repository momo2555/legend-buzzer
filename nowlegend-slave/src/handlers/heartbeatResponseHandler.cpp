#include "handlers/heartbeatResponseHandler.h"

HeartbeatResponseHandler::HeartbeatResponseHandler(std::shared_ptr<RouterInterface> router)
    : BaseHandler {router}
{

}

void HeartbeatResponseHandler::handle(Request *request)
{
   
}

bool HeartbeatResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::HEARTBEAT_RESPONSE;
    
}
