#include "router.h"

Router::Router(std::shared_ptr<Transmission> com)
{
    this->com_ = com;
}

void Router::route(Request *request, MacAddress address)
{
    Serial.println("Router : Route the request");   
    if(request->getReceiverType() == Entity::DEVICE) {
        Serial.println("Router : device destinaton");   
        com_->sendOnce(address, request, true);
    } else if (request->getReceiverType() == Entity::CONTROLLER ||
               request->getReceiverType() == Entity::MONITOR) {
        //talk on the serial port interface
        
    }else {
        Serial.println("Router : Reciver unknown");
    }
}

MacAddress Router::getMyAddress()
{
    MacAddress myAddress{};
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
    return myAddress;
}
