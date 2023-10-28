#include "routerInterface.h"

RouterInterface::RouterInterface(std::unique_ptr<Transmission> com)
{
    this->com_ = com;
}

