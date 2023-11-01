#include "handlers/identificationResponseHandler.h"

IdentificationResponseHandler::IdentificationResponseHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine)
    : BaseHandler {router, deviceManager},
    stateMachine(stateMachine)
{

}

void IdentificationResponseHandler::handle(Request *request)
{
   
}

bool IdentificationResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::CONFIRM_IDENTITY;
    
}
