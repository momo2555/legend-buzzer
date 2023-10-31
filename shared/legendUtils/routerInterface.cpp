#include "routerInterface.h"

RouterInterface::RouterInterface(std::shared_ptr<Transmission> com)
{
    this->com_ = com;
}

void RouterInterface::route(Request *request, MacAddress address)
{
    Serial.println("Router : Route the request");   
    if(request->getReceiver() == Entity::DEVICE) {
        Serial.println("Router : device destinaton");   
        com_->sendOnce(address, request, true);
    } else if (request->getReceiver() == Entity::CONTROLLER ||
               request->getReceiver() == Entity::MONITOR) {
        //talk on the serial port interface
        
    }
}
