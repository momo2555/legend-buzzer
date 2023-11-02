#ifndef IDENTIFICATION_HANDLER_H
#define IDENTIFICATION_HANDLER_H

#include "baseHandler.h"

class IdentificationHandler : public BaseHandler 
{
public:
    IdentificationHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager);
    void handle(Request *request);
    bool canHandle(Request *request);

};

#endif