#ifndef ECHO_RESPONSE_HANDLER_H
#define ECHO_RESPONSE_HANDLER_H

#include "baseHandler.h"

class EchoResponseHandler : public BaseHandler 
{
public:
    EchoResponseHandler(std::shared_ptr<RouterInterface> router);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;

};

#endif