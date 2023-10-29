#include "handlers/identificationHandler.h"

IdentificationHandler::IdentificationHandler(std::shared_ptr<RouterInterface> router)
    : BaseHandler {router}
{

}

void IdentificationHandler::handle(Request *request)
{
}

bool IdentificationHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::IDENTIFICATION;
}
