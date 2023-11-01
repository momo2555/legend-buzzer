#include "handlers/identificationResponseHandler.h"

IdentificationResponseHandler::IdentificationResponseHandler(std::shared_ptr<RouterInterface> router)
    : BaseHandler {router}
{

}

void IdentificationResponseHandler::handle(Request *request)
{
   
}

bool IdentificationResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::CONFIRM_IDENTITY;
    
}
