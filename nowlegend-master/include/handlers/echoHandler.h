#ifndef ECHO_HANDLER_H
#define ECHO_HANDLER_H

#include "baseHandler.h"

class EchoHandler : public BaseHandler 
{
public:
    void handle(Request request);

};

#endif