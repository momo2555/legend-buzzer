#include "handlers/heartbeatResponseHandler.h"

HeartbeatResponseHandler::HeartbeatResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void HeartbeatResponseHandler::handle(Request *request)
{
   Logger::log("Receive heartbeat response request");

    MacAddress deviceAddr{request->getSenderAddress()};


    //update device (set as connected)
    if(this->deviceManager_->containMaster()) {
        Device master {this->deviceManager_->getMaster()};
        if(master.address == deviceAddr) {
            if(this->deviceManager_->isDeviceExist(deviceAddr)) {
                Logger::log("Master connection is OK");
                master.aliveTimer.timer();
                this->deviceManager_->updateDevice(deviceAddr, master);
            }
        }
        
    }
    
}

bool HeartbeatResponseHandler::canHandle(Request *request)
{
   
    return request->getType() == RequestType::HEARTBEAT_RESPONSE;
    
}
