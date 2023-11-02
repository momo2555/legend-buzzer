#ifndef ROUTER_INTERFACE_H
#define ROUTER_INTERFACE_H

#include "transmission.h"
#include "request.h"

class Router 
{
public:
    Router(std::shared_ptr<Transmission> com);
    void route(Request *request, MacAddress address);
private:
    std::shared_ptr<Transmission> com_ {};


};

#endif