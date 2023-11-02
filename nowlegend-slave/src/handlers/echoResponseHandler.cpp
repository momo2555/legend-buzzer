#include "handlers/echoResponseHandler.h"

EchoResponseHandler::EchoResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine)
    : BaseHandler {router, deviceManager}
{
    this->stateMachine = stateMachine;

}

void EchoResponseHandler::handle(Request *request)
{
    Serial.println("receive echo response");
    if(request->getSenderType() == Entity::MASTER) {
        Serial.println("Add Master in devices");
        this->deviceManager_->addMaster(request->getSenderAddress());
        this->stateMachine->transmissionState = TransmissionState::IDENTIFICATION_STATE;
        this->stateMachine->masterRegistered = true;
    }
   
}

bool EchoResponseHandler::canHandle(Request *request)
{
    Serial.println("ECHO CAN HANDLE");
    return request->getType() == RequestType::ECHO_RESPONSE;
    
}
