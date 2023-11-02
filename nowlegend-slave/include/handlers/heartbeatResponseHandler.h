#ifndef HEARTBEAT_RESPONSE_HANDLER_H
#define HEARTBEAT_RESPONSE_HANDLER_H

#include "baseHandler.h"

class HeartbeatResponseHandler : public BaseHandler 
{
public:
    HeartbeatResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;

};

#endif