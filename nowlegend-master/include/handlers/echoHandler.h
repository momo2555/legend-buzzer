#ifndef ECHO_HANDLER_H
#define ECHO_HANDLER_H

#include "baseHandler.h"

class EchoHandler : public BaseHandler 
{
public:
    EchoHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;

};

#endif