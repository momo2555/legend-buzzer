#include "legend.h"

Legend::Legend() {
    com_ = std::make_unique<Transmission>(Transmission());
    req_ = std::make_unique<Request>(Request());
    
    
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddr.data());
    req_->setMacAddress(myAddr);



}
void Legend::enableConfiguration() {

}
void Legend::disableConfiguration() {

}

void Legend::run() {
    com_->initTransmission();
    com_->OnDataRecv<Legend>(this, &Legend::dataRecvCallback_);

}

void Legend::dataRecvCallback_(const unsigned char * addr, const unsigned char * data, int size) {

}

void Legend::subProcess_(void*) {

}

void Legend::sendEcho_() {}
void Legend::sendIdentificationFrame_ () {}
void Legend::sendEchoFrame_() {}