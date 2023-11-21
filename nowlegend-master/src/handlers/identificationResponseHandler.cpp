#include "handlers/identificationResponseHandler.h"

IdentificationResponseHandler::IdentificationResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{
   
}

void IdentificationResponseHandler::handle(Request *request)
{
    Logger::log("Receive identification response");
    if(request->getSenderType() == Entity::MASTER) {
        if (this->deviceManager_->containMaster()) {
            IdentificationResult res = request->getIdentifactionResult();
            if (res == IdentificationResult::ACCEPTED) {
                Logger::log("Identification accpeted !");
                MacAddress deviceAddr = request->getReceiverAddress();
                if(this->deviceManager_->isDeviceExist(deviceAddr)) {
                    Device device = this->deviceManager_->getDevice(deviceAddr);
                    device.state = ConnectionState::CONNECTED;
                    device.aliveTimer.timer();
                    this->deviceManager_->updateDevice(deviceAddr, device);
                }
                router_->route(request, {});
                
            } else {
                Logger::log("Identification refused !");
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
