#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

#include "request.h"
#include "routerInterface.h"
#include "deviceManager.h"

class BaseHandler
{

public:
    BaseHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager);
    virtual void handle(Request *request) {};
    virtual bool canHandle(Request *request) {return false;};
protected:
    std::shared_ptr<RouterInterface> router_ {};
    std::shared_ptr<DeviceManager> deviceManager_ {};
};

#endif


