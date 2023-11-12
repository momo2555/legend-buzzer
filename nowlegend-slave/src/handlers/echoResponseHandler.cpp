#include "handlers/echoResponseHandler.h"

EchoResponseHandler::EchoResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine)
    : BaseHandler {router, deviceManager}
{
    this->stateMachine = stateMachine;

}

void EchoResponseHandler::handle(Request *request)
{
    Logger::log("receive echo response");
    if(request->getSenderType() == Entity::MASTER) {
        Logger::log("Add Master in devices");
        this->deviceManager_->addMaster(request->getSenderAddress());
        this->stateMachine->transmissionState = TransmissionState::IDENTIFICATION_STATE;
        this->stateMachine->masterRegistered = true;
    }
   
}

bool EchoResponseHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::ECHO_RESPONSE;
    
}
