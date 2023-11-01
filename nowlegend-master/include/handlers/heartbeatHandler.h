#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "baseHandler.h"

class HeartbeatHandler : public BaseHandler 
{
public:
    HeartbeatHandler(std::shared_ptr<RouterInterface> router, std::shared_ptr<DeviceManager> deviceManager);
    void handle(Request *request);
    bool canHandle(Request *request);

};

#endif