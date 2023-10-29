#ifndef IDENTIFICATION_HANDLER_H
#define IDENTIFICATION_HANDLER_H

#include "baseHandler.h"

class IdentificationHandler : public BaseHandler 
{
public:
    IdentificationHandler(std::shared_ptr<RouterInterface> router);
    void handle(Request *request);
    bool canHandle(Request *request);

};

#endif