#include "handlers/identificationResponseHandler.h"

IdentificationResponseHandler::IdentificationResponseHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine)
    : BaseHandler {router, deviceManager}
{
    this->stateMachine = stateMachine;
}

void IdentificationResponseHandler::handle(Request *request)
{
    Serial.println("Receive identification response");
    if(request->getSenderType() == Entity::MASTER) {
        if (this->deviceManager_->containMaster()) {
            Device master = this->deviceManager_->getMaster();
            IdentificationResult res = request->getIdentifactionResult();
            Serial.println("Read the identification result = " + String(res));
            if (res == IdentificationResult::ACCEPTED) {
                Serial.println("Identification accepted");
                master.state = ConnectionState::CONNECTED;
                this->deviceManager_->updateDevice(master.address, master);
                //update the state machine
                this->stateMachine->transmissionState = TransmissionState::READY_STATE;
                this->stateMachine->masterRegistered = true;

            }
        }else {
            Serial.println("The master server identy wasn't registered");
        }
        
        
    }

}

bool IdentificationResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::CONFIRM_IDENTITY;
    
}
