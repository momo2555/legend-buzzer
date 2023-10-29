#include "routerInterface.h"

RouterInterface::RouterInterface(std::shared_ptr<Transmission> com)
{
    this->com_ = com;
}

void RouterInterface::route(Request *request, MacAddress address)
{
}
