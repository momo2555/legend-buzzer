#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "baseHandler.h"

class MessageHandler : public BaseHandler 
{
public:
    MessageHandler(std::shared_ptr<RouterInterface> router);
    void handle(Request *request) override;
    bool canHandle(Request *request) override;

};

#endif