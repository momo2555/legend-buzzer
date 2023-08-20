#ifndef LEGEND_H
#define LEGEND_H

#include <iostream>
#include <string>
#include <memory>

#include <request.h>
#include <transmission.h>
#include <fct_utils.h>

enum TransmissionState {
    ECHO_STANDBY = 0,
    IDENTIFICATION_STATE,
    READY_STATE,
};

struct LegendStateMachine {
    TransmissionState transmissionState {ECHO_STANDBY};
};

class Legend {
    public:
        Legend();
        void enableConfiguration();
        void disableConfiguration();
        void setDefaultPassword(std::string& password);
        void setDefaultSSID(std::string& ssid);

        void run();
        bool isReady();


    private:
        void sendEcho_();
        void sendIdentificationFrame_ ();
        void sendEchoFrame_();
        void dataRecvCallback_(const unsigned char * addr, const unsigned char * data, int size);
        void subProcess_(void*);
        std::unique_ptr<Transmission> com_ {};
        std::unique_ptr<Request> req_ {};
        LegendStateMachine stateMachine {};
        MacAddress myAddr {};
        MacAddress masterAddr {};
       



};
#endif