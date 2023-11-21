#ifndef LEGEND_MASTER_H
#define LEGEND_MASTER_H

#include "transmission.h"
#include "request.h"
#include "router.h"
#include "handlerManager.h"
#include "handlers/echoHandler.h"
#include "handlers/identificationHandler.h"
#include "handlers/messageHandler.h"
#include "handlers/heartbeatHandler.h"
#include "handlers/identificationResponseHandler.h"

class LegendMaster
{
    // respond to echos
    // identifiying
    // send and read the serial port
public:
    LegendMaster();
    //~LegendMaster(){};
    void run();
    void setup();

private:
    void dataRecvCallback_(const unsigned char *addr, const unsigned char *data, int size);
    
    Transmission::ptr com_ {};
    SerialportInterface::ptr serial_ {};
    std::shared_ptr<Router> router_ {};
    std::shared_ptr<DeviceManager> deviceManager_ {};
    std::unique_ptr<HandlerManager> handlerManager_ {};


};

#endif
