#ifndef ECHO_RESPONSE_HANDLER_H
#define ECHO_RESPONSE_HANDLER_H

#include "baseHandler.h"
#include "stateMachine.h"

class EchoResponseHandler : public BaseHandler 
{
public:
    EchoResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;
private:
    LegendStateMachine* stateMachine {};

};

#endif