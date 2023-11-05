#include "router.h"

Router::Router(Transmission::ptr com, SerialportInterface::ptr serial)
{
    this->com_ = com;
    this->serial_ = serial;
    
}

void Router::route(Request *request, MacAddress address)
{
    Serial.println("Router : Route the request");   
    if(request->getReceiverType() == Entity::DEVICE) {
        Serial.println("Router : device destinaton");   
        com_->sendOnce(address, request, true);
    } else if (request->getReceiverType() == Entity::CONTROLLER ||
               request->getReceiverType() == Entity::MONITOR ||
               request->getReceiverType() == Entity::MASTER) {
        //talk on the serial port interface
        Serial.println("Router : SEND TO MASTER");
        serial_->writeRequest(request);
        
    }else {
        Serial.println("Router : Reciver unknown");
    }
}
