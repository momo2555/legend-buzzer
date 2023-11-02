#ifndef IDENTIFICATION_REPONSE_HANDLER_H
#define IDENTIFICATION_REPONSE_HANDLER_H

#include "baseHandler.h"
#include "stateMachine.h"

class IdentificationResponseHandler : public BaseHandler 
{
public:
    IdentificationResponseHandler(std::shared_ptr<Router> router, std::shared_ptr<DeviceManager> deviceManager, LegendStateMachine* stateMachine);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;
private:
    LegendStateMachine* stateMachine {};

};

#endif