#include "handlers/heartbeatHandler.h"

HeartbeatHandler::HeartbeatHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager)
    : BaseHandler {router, deviceManager}
{

}

void HeartbeatHandler::handle(Request *request)
{
    Logger::log("Receive heartbeat request");
    auto heartbeatResponseReq = std::make_unique<Request>(Request());
    heartbeatResponseReq->asHeartbeatResponse();

    MacAddress myAddress{Transmission::getMyAddress()};
    MacAddress deviceAddr{request->getSenderAddress()};
    heartbeatResponseReq->setSender(Entity::MASTER, myAddress);
    heartbeatResponseReq->setReceiver(Entity::DEVICE, deviceAddr);

    //update device (set as connected)
    if(this->deviceManager_->isDeviceExist(deviceAddr)) {
        Device device = this->deviceManager_->getDevice(deviceAddr);
        device.aliveTimer.timer();
        this->deviceManager_->updateDevice(deviceAddr, device);
    }
    this->router_->route(heartbeatResponseReq.get(), deviceAddr);
}

bool HeartbeatHandler::canHandle(Request *request)
{
    return request->getType() == RequestType::HEARTBEAT;
}
