#include "transmission.h"

void receiveCallbackWrapper(const unsigned char *a, const unsigned char *b, int c)
{
    receiveCallback(a, b, c);
}
void setReceiveCallback(ReceiveCallback cb)
{
    receiveCallback = cb;
}

Transmission::Transmission()
{
}

void Transmission::registerPeer(MacAddress address)
{
    // check if the address is in the peers list
    if (!esp_now_is_peer_exist(address.data()))
    {
        // Register peer
        esp_now_peer_info_t peerInfo {};
        // peerInfo.ifidx=WIFI_IF_AP;
        memcpy(peerInfo.peer_addr, address.data(), 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;

        // Add peer
        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            Logger::log("Failed to add peer");
            return;
        }
    }
}
void Transmission::registerEchoPeer()
{
    MacAddress echoBroadAddr ECHO_BROADCAST_ADDR;
    registerPeer(echoBroadAddr);
}
void Transmission::deleteEchoPeer()
{
    MacAddress echoBroadAddr ECHO_BROADCAST_ADDR;
    deletePeer(echoBroadAddr);
}
void Transmission::deletePeer(MacAddress address)
{
    if(esp_now_is_peer_exist(address.data())) {
        esp_now_del_peer(address.data());
    }
}

MacAddress Transmission::getMyAddress()
{
    MacAddress addr {std::string(WiFi.macAddress().c_str())};
    return addr;
}

bool Transmission::isPeerRegistered(MacAddress address)
{
    return esp_now_del_peer(address.data());
}
void Transmission::initTransmission()
{

    WiFi.mode(WIFI_STA);
    myAddress = std::string(WiFi.macAddress().c_str());

    if (esp_now_init() != ESP_OK)
    {
        Logger::log("Error initializing ESP-NOW");
        return;
    }
    
}
void Transmission::send(uint8_t address[], uint8_t *message, uint8_t len)
{
    esp_err_t result = esp_now_send(address, message, len);
    if (result == ESP_OK)
    {
        // Logger::log("sended ok");
    }
    else
    {
        // Logger::log("Error sending the data");
    }
    delay(3);
}

void Transmission::broadcastAll(uint8_t *message, uint8_t len)
{
    uint8_t broad[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    send(broad, message, len);
}

void Transmission::sendAll(uint8_t *message, uint8_t len)
{
        send(0, message, len);
}

void Transmission::send(MacAddress address, Request *request, SendMethod method)
{
    auto requestBody = request->getRequestBody();
    if (method == SendMethod::SINGLE) 
    {
        send(address.data(), (uint8_t *)&(requestBody), sizeof(requestBody));
    }
    else if (method == SendMethod::BROADCAST) {
        broadcastAll((uint8_t *)&(requestBody), sizeof(requestBody));
    }
        

    delayMicroseconds(500);
}
void Transmission::sendOnce(MacAddress address, Request* request, bool strict) {
    auto requestBody = request->getRequestBody();
    bool registered = isPeerRegistered(address);
    if(!registered) {
        Logger::log("register the new peer");
        registerPeer(address);
    }
    send(address, request);
    if(strict && registered) {
        deletePeer(address);
    }
    
}

void Transmission::OnDataSent(void (*callBack)(const unsigned char *, esp_now_send_status_t))
{
    esp_now_register_send_cb(*callBack);
}
