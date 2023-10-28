#ifndef HANDLER_MANAGER_H
#define HANDLER_MANAGER_H

#include "routerInterface.h"
#include "transmission.h"
#include "request.h"

class HandlerManger
{
public:
    HandlerManger(std::shared_ptr<RouterInterface> router);
private:
    std::shared_ptr<RouterInterface> router_ {};
};

#endif