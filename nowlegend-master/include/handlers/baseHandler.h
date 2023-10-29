#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

#include "request.h"
#include "routerInterface.h"

class BaseHandler
{

public:
    BaseHandler(std::shared_ptr<RouterInterface> router);
    void handle(Request request);
    bool canHandle(Request request);
private:
    std::shared_ptr<RouterInterface> router_ {};

};

#endif


