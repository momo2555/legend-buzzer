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

    auto receivedRequest = std::make_unique<Request>(Request(data, size));
    switch(receivedRequest->getType()) {
        case RequestType::ECHO_RESPONSE: // STEP 1
            // receive the echo response : save the master address and send identification
            break;
        case RequestType::CONFIRM_IDENTITY: // STEP 2
            // The master confirm the identification
            break;
        case RequestType::DEVICE_DATA: 
            // Receive new data
            break;
        case RequestType::DEVICE_EVENT:
            //receive a new event
            break;
        default:
            break;
    }

}

void Legend::subProcess() {
    
    switch (stateMachine_.transmissionState) {
        case TransmissionState::ECHO_STANDBY :
            // Send every second an echo
            break;

        case TransmissionState::IDENTIFICATION_STATE :
            break;
        
        case TransmissionState::READY_STATE :
            // Send an alive Request 
            break;

        default:
            break;
    }
    Serial.println("coucou");
    delay(8);
    
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