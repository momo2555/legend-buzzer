#ifndef IDENTIFICATION_REPONSE_HANDLER_H
#define IDENTIFICATION_REPONSE_HANDLER_H

#include "baseHandler.h"

class IdentificationResponseHandler : public BaseHandler 
{
public:
    IdentificationResponseHandler(std::shared_ptr<RouterInterface> router);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;

};

#endif