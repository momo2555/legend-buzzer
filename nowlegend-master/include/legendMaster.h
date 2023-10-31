#ifndef LEGEND_MASTER_H
#define LEGEND_MASTER_H

#include "transmission.h"
#include "request.h"
#include "routerInterface.h"
#include "handlerManager.h"
#include "handlers/echoHandler.h"
#include "handlers/identificationHandler.h"
#include "handlers/messageHandler.h"
#include "handlers/heartbeatHandler.h"

class LegendMaster
{
    // respond to echos
    // identifiying
    // send and read the serial port
public:
    LegendMaster();
    //~LegendMaster(){};
    void run();

private:
    void dataRecvCallback_(const unsigned char *addr, const unsigned char *data, int size);
    
    std::shared_ptr<Transmission> com_ {};
    std::shared_ptr<RouterInterface> router_ {};
    std::unique_ptr<HandlerManager> handlerManager_ {};


};

#endif
