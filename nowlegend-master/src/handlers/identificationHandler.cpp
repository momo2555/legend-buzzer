#include "handlers/identificationHandler.h"

IdentificationHandler::IdentificationHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void IdentificationHandler::handle(Request *request)
{
}

bool IdentificationHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::IDENTIFICATION;
}
