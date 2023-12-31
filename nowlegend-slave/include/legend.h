#ifndef LEGEND_H
#define LEGEND_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include <request.h>
#include <transmission.h>
#include <fct_utils.h>
#include <timer.h>

#include "handlerManager.h"
#include "router.h"
#include "stateMachine.h"
#include "serialportInterface.h"
#include "handlers/echoResponseHandler.h"
#include "handlers/heartbeatResponseHandler.h"
#include "handlers/identificationResponseHandler.h"
#include "handlers/messageHandler.h"
#include "freertos/semphr.h"

typedef Timer* TimerPtr;

void legendTask (void * param);

class Legend {
    public:
        Legend();
        void run();
        bool isReady();
        void subProcess();
        void sendRequest(Request request, Entity receiver);

    private:
        void createSubProcess_ ();
        void sendIdentificationFrame_ ();
        void sendEchoFrame_ ();
        void sendAliveFrame_();
        void checkHeartbeat_();
        void dataRecvCallback_ (const unsigned char * addr, const unsigned char * data, int size);
        bool isMasterRegistered_();
        
        // interfaces
        Transmission::ptr com_ {};
        SerialportInterface::ptr serial_ {};

        std::unique_ptr<Request> req_ {};
        std::shared_ptr<Router> router_ {};
        std::shared_ptr<DeviceManager> deviceManager_ {};
        std::unique_ptr<HandlerManager> handlerManager_ {};

        LegendStateMachine *stateMachine_ {};
        MacAddress myAddr_ {};
        MacAddress masterAddr_ {};

        //fake timers
        TimerPtr echoTimer_ {};
        TimerPtr identificationTimer_ {};
        TimerPtr aliveTimer_ {};
        void initAllTimers_();

        // mutex
        SemaphoreHandle_t xSemaphore = NULL;

        bool isSubprocessLaunched {false};
    
};
#endif