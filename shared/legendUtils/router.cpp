#include "router.h"

Router::Router(Transmission::ptr com, SerialportInterface::ptr serial)
{
    this->com_ = com;
    this->serial_ = serial;
    
}

void Router::route(Request *request, MacAddress address)
{
    Logger::log("Router : Route the request");   
    if(request->getReceiverType() == Entity::DEVICE) {
        Logger::log("Router : device destinaton");   
        com_->sendOnce(request->getReceiverAddress(), request, true);
    } else if (request->getReceiverType() == Entity::CONTROLLER ||
               request->getReceiverType() == Entity::MONITOR ||
               request->getReceiverType() == Entity::MASTER) {
        //talk on the serial port interface
        Logger::log("Router : SEND TO MASTER");
        serial_->writeRequest(request);
        
    }else {
        Logger::log("Router : Reciver unknown");
    }
}
