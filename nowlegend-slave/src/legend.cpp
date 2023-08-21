#include "legend.h"


TaskHandle_t subProc;

Legend::Legend() {
    com_ = std::make_unique<Transmission>(Transmission());
    req_ = std::make_unique<Request>(Request());
    
    
    macAddressToIntArray(WiFi.macAddress().c_str(), myAddr_.data());
    req_->setMacAddress(myAddr_);

    



}
void Legend::enableConfiguration() {

}
void Legend::disableConfiguration() {

}

void Legend::run() {
    com_->initTransmission();
    com_->OnDataRecv<Legend>(this, &Legend::dataRecvCallback_);
    createSubProcess_();

}
void Legend::createSubProcess_() {
    //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
    
    xTaskCreatePinnedToCore(
                        legendTask,   /* Task function. */
                        "legendTask",     /* name of task. */
                        10000,       /* Stack size of task */
                        (void*)this,        /* parameter of the task */
                        1,           /* priority of the task */
                        &subProc,      /* Task handle to keep track of created task */
                        0);          /* pin task to core 0 */ 

    delay (500);
}
void Legend::dataRecvCallback_(const unsigned char * addr, const unsigned char * data, int size) {

}

void Legend::subProcess() {
    Serial.println("coucou");
    delay(500);
}

void Legend::sendEcho_() {}
void Legend::sendIdentificationFrame_ () {}
void Legend::sendEchoFrame_() {}

void legendTask (void * param) {
    while(true) {
        Serial.println("coucocu you ");
        Legend* legend = (Legend*)param;
        legend->subProcess();
    }

}