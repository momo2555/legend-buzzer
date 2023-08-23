#include "legend.h"

TaskHandle_t subProc;

Legend::Legend()
{
    com_ = std::make_unique<Transmission>(Transmission());
    req_ = std::make_unique<Request>(Request());

    macAddressToIntArray(WiFi.macAddress().c_str(), myAddr_.data());
    req_->setMacAddress(myAddr_);

    echoTimer_ = std::make_unique<Timer>(Timer());
    identificationTimer_ = std::make_unique<Timer>(Timer());
    aliveTimer_ = std::make_unique<Timer>(Timer());
}

void Legend::enableConfiguration()
{
}

void Legend::disableConfiguration()
{
}

void Legend::run()
{
    com_->initTransmission();
    com_->registerEchoPeer();
    com_->OnDataRecv<Legend>(this, &Legend::dataRecvCallback_);
    createSubProcess_();
}

void Legend::createSubProcess_()
{
    if (!isSubprocessLaunched)
    {
        initAllTimers_();
        xTaskCreatePinnedToCore(
            legendTask,   /* Task function. */
            "legendTask", /* name of task. */
            10000,        /* Stack size of task */
            (void *)this, /* parameter of the task */
            1,            /* priority of the task */
            &subProc,     /* Task handle to keep track of created task */
            0);           /* pin task to core 0 */

        delay(500);
    }
}
void Legend::dataRecvCallback_(const unsigned char *addr, const unsigned char *data, int size)
{

    auto receivedRequest = std::make_unique<Request>(Request(data, size));
    switch (receivedRequest->getType())
    {
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
        // receive a new event
        break;
    default:
        break;
    }
}

void Legend::subProcess()
{
    if(!isSubprocessLaunched) isSubprocessLaunched = true;
    switch (stateMachine_.transmissionState)
    {
    case TransmissionState::ECHO_STANDBY:
        // Send every second an echo
        if (echoTimer_->isElapsed(1000))
        {
            echoTimer_->timer();
            sendEchoFrame_();
        }
        break;

    case TransmissionState::IDENTIFICATION_STATE:
        // Send identification frame
        if (identificationTimer_->isElapsed(2000))
        {
            identificationTimer_->timer();
            sendIdentificationFrame_();
        }
        break;

    case TransmissionState::READY_STATE:
        // Send an alive Request
        if (aliveTimer_->isElapsed(2000))
        {
            aliveTimer_->timer();
            sendAliveFrame_();
        }
        break;

    default:
        break;
    }
    Serial.println("coucou");
    delay(8);
}
bool Legend::isMasterRegistered_()
{
    return stateMachine_.masterRegistered;
}
void Legend::sendIdentificationFrame_()
{
    if (isMasterRegistered_() && stateMachine_.transmissionState == TransmissionState::IDENTIFICATION_STATE)
    {
        auto identifyReq = std::make_unique<Request>(Request());
        identifyReq->asIdentification();
        MacAddress myAddress{};
        macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
        identifyReq->setMacAddress(myAddress);
        com_->send(masterAddr_, identifyReq.get());
    }
}
void Legend::sendEchoFrame_()
{
    // broadcast an echo message
    if (!isMasterRegistered_() && stateMachine_.transmissionState == TransmissionState::ECHO_STANDBY)
    {
        auto echoReq = std::make_unique<Request>(Request());
        echoReq->asEcho();
        MacAddress myAddress{};
        macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
        echoReq->setMacAddress(myAddress);
        MacAddress emptyAddr {};
        com_->send(emptyAddr, echoReq.get(), SendMethod::BROADCAST);
    }
}
void Legend::sendAliveFrame_() {
    if (isMasterRegistered_() && stateMachine_.transmissionState == TransmissionState::READY_STATE)
    {
        auto identifyReq = std::make_unique<Request>(Request());
        /*identifyReq->as();
        MacAddress myAddress{};
        macAddressToIntArray(WiFi.macAddress().c_str(), myAddress.data());
        identifyReq->setMacAddress(myAddress);
        com_->send(masterAddr_, identifyReq.get());*/
    }
}

void Legend::initAllTimers_()
{
    identificationTimer_->timer();
    echoTimer_->timer();
    aliveTimer_->timer();
}

void legendTask(void *param)
{
    while (true)
    {
        Serial.println("coucocu you ");
        Legend *legend = (Legend *)param;
        legend->subProcess();
    }
}
