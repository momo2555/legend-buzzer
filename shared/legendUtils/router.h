#ifndef ROUTER_INTERFACE_H
#define ROUTER_INTERFACE_H

#include "transmission.h"
#include "serialportInterface.h"
#include "request.h"

class Router 
{
public:
    Router(Transmission::ptr com, SerialportInterface::ptr serial);
    void route(Request *request, MacAddress address);
private:
    Transmission::ptr com_ {};
    SerialportInterface::ptr serial_ {};


};

#endif