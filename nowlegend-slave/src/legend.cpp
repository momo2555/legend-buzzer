#include "legend.h"

TaskHandle_t subProc;

Legend::Legend()
{
    com_ = std::make_shared<Transmission>(Transmission());
    com_->initTransmission();
    serial_ = std::make_shared<SerialportInterface>(SerialportInterface());
    serial_->init();

    myAddr_ = std::string(WiFi.macAddress().c_str());

    //init the state machine
    stateMachine_ = new LegendStateMachine();
    stateMachine_->transmissionState = TransmissionState::ECHO_STANDBY;
    stateMachine_->masterRegistered = false;

    echoTimer_ = new Timer();
    identificationTimer_ =  new Timer();
    aliveTimer_ =  new Timer();

    router_ = std::make_shared<Router>(Router(com_, serial_));
    deviceManager_ = std::make_shared<DeviceManager>(DeviceManager());
    handlerManager_ = std::make_unique<HandlerManager>(HandlerManager(router_));
    

    auto echoResponseHandler = new EchoResponseHandler(router_, deviceManager_, stateMachine_);
    auto messageHandler = new MessageHandler(router_, deviceManager_);
    auto heartbeatResponseHandler = new HeartbeatResponseHandler(router_, deviceManager_);
    auto identificationResponseHandler = new IdentificationResponseHandler(router_, deviceManager_, stateMachine_);

    handlerManager_->addHandler(echoResponseHandler);
    handlerManager_->addHandler(messageHandler);
    handlerManager_->addHandler(heartbeatResponseHandler);
    handlerManager_->addHandler(identificationResponseHandler);
}

void Legend::run()
{
    
    com_->registerEchoPeer();
    com_->OnDataRecv<Legend>(this, &Legend::dataRecvCallback_);
    com_->OnDataSent([](const unsigned char * addr, esp_now_send_status_t status){
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        Serial.println("frame sent");
    });
    
    createSubProcess_();
}

bool Legend::isReady()
{
    return stateMachine_->transmissionState == TransmissionState::READY_STATE;
}

void Legend::createSubProcess_()
{
    Serial.println("Create sub process");
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

    Serial.println("receive data");
    auto receivedRequest = std::make_unique<Request>(Request(data, size));
    this->handlerManager_->handleRequest(receivedRequest.get());
}

void Legend::subProcess()
{
    if(!isSubprocessLaunched) isSubprocessLaunched = true;
    switch (stateMachine_->transmissionState)
    {
    case TransmissionState::ECHO_STANDBY:
        // Send every second an echo
        if (echoTimer_->isElapsed(1000))
        {
            Serial.println("before send echo frame");
            echoTimer_->timer();
            sendEchoFrame_();
        }
        break;

    case TransmissionState::IDENTIFICATION_STATE:
        // Send identification frame
        if (identificationTimer_->isElapsed(2000))
        {
            Serial.println("before send id frame");
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
        checkHeartbeat_();
        break;

    default:
        break;
    }
    delay(20);
}
void Legend::sendRequest(Request request, Entity receiver)
{
    if(isReady()) {
        MacAddress myAddress {Transmission::getMyAddress()};
        MacAddress masterAddr {deviceManager_->getMaster().address};
        request.setReceiver(receiver, masterAddr);
        request.setSender(Entity::DEVICE, myAddress);
        com_->sendOnce(masterAddr, &request, true);
    }
}

bool Legend::isMasterRegistered_()
{
    return stateMachine_->masterRegistered;
}

void Legend::sendIdentificationFrame_()
{
    Serial.println("send identification frame");
    if (isMasterRegistered_() && stateMachine_->transmissionState == TransmissionState::IDENTIFICATION_STATE)
    {
        auto identifyReq = std::make_unique<Request>(Request());
        identifyReq->asIdentification();
        MacAddress myAddress {Transmission::getMyAddress()};
        MacAddress masterAddr = deviceManager_->getMaster().address;
        identifyReq->setSender(Entity::DEVICE, myAddress);
        identifyReq->setReceiver(Entity::MASTER, masterAddr);
        com_->registerPeer(masterAddr.data());
        com_->send(masterAddr, identifyReq.get());
    }
}
void Legend::sendEchoFrame_()
{
    Serial.println("send echo frame");
    if (!isMasterRegistered_() && stateMachine_->transmissionState == TransmissionState::ECHO_STANDBY)
    {   
        Serial.println("send echo");
        auto echoReq = std::make_unique<Request>(Request());
        echoReq->asEcho();
        MacAddress myAddress {Transmission::getMyAddress()};
        echoReq->setSender(Entity::DEVICE, myAddress);
        //MacAddress emptyAddr {};
        //com_->send(emptyAddr, echoReq.get(), SendMethod::BROADCAST);
        MacAddress emptyAddr {};
        com_->send(emptyAddr, echoReq.get(), SendMethod::BROADCAST);
        //com_->sendOnce(emptyAddr, echoReq.get(), true);
    }
}
void Legend::sendAliveFrame_() {
    Serial.println("send heartbeat frame");
    if (isMasterRegistered_() && stateMachine_->transmissionState == TransmissionState::READY_STATE)
    {
        
        auto heartbeatReq = std::make_unique<Request>(Request());
        heartbeatReq->asHeartbeat();
        MacAddress myAddress {Transmission::getMyAddress()};
        MacAddress masterAddr = deviceManager_->getMaster().address;
        heartbeatReq->setSender(Entity::DEVICE, myAddress);
        heartbeatReq->setReceiver(Entity::MASTER, masterAddr);
        Serial.println("before sending hertbeat");
        //com_->registerPeer(masterAddr.data());
        com_->send(masterAddr, heartbeatReq.get());
    }
}

void Legend::checkHeartbeat_()
{
    if (isMasterRegistered_() && stateMachine_->transmissionState == TransmissionState::READY_STATE){
        if(deviceManager_->containMaster()) {
            Device master = deviceManager_->getMaster();
            if (master.aliveTimer.isElapsed(3000)) {
                Serial.println("Master watchdog triggered");
                stateMachine_->transmissionState = TransmissionState::ECHO_STANDBY;
                stateMachine_->masterRegistered = false;
                deviceManager_.reset();
                
            }
        }
        

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
    Serial.println("run legend loop");
    while (true)
    {
        //Serial.println("coucou you ");
        Legend *legend = (Legend *)param;
        legend->subProcess();
    }
}
