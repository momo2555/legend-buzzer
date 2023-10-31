#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

#include "request.h"
#include "routerInterface.h"

class BaseHandler
{

public:
    BaseHandler(std::shared_ptr<RouterInterface> router);
    virtual void handle(Request *request) {};
    
    virtual bool canHandle(Request *request) {Serial.println("BaseHandler : canHandle");return false;};
protected:
    std::shared_ptr<RouterInterface> router_ {};

};

#endif


