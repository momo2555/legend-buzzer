#include "handlers/identificationResponseHandler.h"

IdentificationResponseHandler::IdentificationResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine)
    : BaseHandler {router, deviceManager}
{
    this->stateMachine = stateMachine;
}

void IdentificationResponseHandler::handle(Request *request)
{
    Logger::log("Receive identification response");
    if(request->getSenderType() == Entity::MASTER) {
        if (this->deviceManager_->containMaster()) {
            Device master = this->deviceManager_->getMaster();
            IdentificationResult res = request->getIdentifactionResult();
            Logger::log("Read the identification result = " + std::string(String((int)res).c_str()));
            if (res == IdentificationResult::ACCEPTED) {
                Logger::log("Identification accepted");
                master.state = ConnectionState::CONNECTED;
                master.aliveTimer.timer();
                this->deviceManager_->updateDevice(master.address, master);
                //update the state machine
                this->stateMachine->transmissionState = TransmissionState::READY_STATE;
                this->stateMachine->masterRegistered = true;

            }
        }else {
            Logger::log("The master server identy wasn't registered");
        }
        
        
    }

}

bool IdentificationResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::CONFIRM_IDENTITY;
    
}
