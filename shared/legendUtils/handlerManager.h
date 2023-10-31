#ifndef HANDLER_MANAGER_H
#define HANDLER_MANAGER_H

#include "routerInterface.h"
#include "transmission.h"
#include "request.h"

#include "baseHandler.h"


class HandlerManager
{
public:
    HandlerManager(std::shared_ptr<RouterInterface> router);
    void handleRequest(Request *request);
    void addHandler(BaseHandler *handler);
private:
    std::shared_ptr<RouterInterface> router_ {};
    std::vector<BaseHandler*> handlers_ {};
    
};

#endif