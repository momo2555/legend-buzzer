#ifndef HANDLER_MANAGER_H
#define HANDLER_MANAGER_H

#include "router.h"
#include "transmission.h"
#include "request.h"

#include "baseHandler.h"
#include "logger.h"


class HandlerManager
{
public:
    HandlerManager(std::shared_ptr<Router> router);
    void handleRequest(Request *request);
    void addHandler(BaseHandler *handler);
private:
    std::shared_ptr<Router> router_ {};
    std::vector<BaseHandler*> handlers_ {};
    
};

#endif