#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

#include "request.h"
#include "router.h"
#include "deviceManager.h"
#include "logger.h"

class BaseHandler
{

public:
    BaseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager);
    virtual void handle(Request *request) {};
    virtual bool canHandle(Request *request) {return false;};
protected:
    std::shared_ptr<Router> router_ {};
    std::shared_ptr<DeviceManager> deviceManager_ {};
};

#endif


