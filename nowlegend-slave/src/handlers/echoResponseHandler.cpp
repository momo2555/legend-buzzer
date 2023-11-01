#include "handlers/echoResponseHandler.h"

EchoResponseHandler::EchoResponseHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void EchoResponseHandler::handle(Request *request)
{
   Serial.println("receive echo response");
}

bool EchoResponseHandler::canHandle(Request *request)
{
    Serial.println("ECHO CAN HANDLE");
    return request->getType() == RequestType::ECHO_RESPONSE;
    
}
