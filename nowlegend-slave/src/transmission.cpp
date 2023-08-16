#include "com.h"

Transmission::Transmission() {
  
}
void Transmission::registerPeer(String address){
  char charAddress[20];
  uint8_t intAddress[6];
  address.toCharArray(charAddress, 20);

  macAddressToIntArray(charAddress, intAddress);
  registerPeer(intAddress);
}
void Transmission::registerPeer(uint8_t address[]) {
  //check if the address is in the peers list
  if(!esp_now_is_peer_exist(address)) {
    // Register peer
    esp_now_peer_info_t peerInfo = {};
    //peerInfo.ifidx=WIFI_IF_AP;
    memcpy(peerInfo.peer_addr, address, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    // Add peer       
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      return;
    }
    //add peer to the registered tab
    memcpy(peerAdresses[peerIndex], address, 6);
    peerIndex++;
  }
  
}
void Transmission::deletePeer(uint8_t address[]) {
  uint8_t newPeerIndex = peerIndex;
    for(uint8_t i = 0;i<newPeerIndex;i++) {
        //compare addresses
        if(compareAddresses(peerAdresses[i], address)) {
            //invert addresses in address tab
            uint8_t last[6];
            memcpy(last, peerAdresses[newPeerIndex - 1], 6);
            memcpy(peerAdresses[newPeerIndex - 1], peerAdresses[i], 6);
            memcpy(peerAdresses[i], last, 6);
            newPeerIndex--;
            //delete peer from peer list
            esp_now_del_peer(address);
            setWithholding(address, false);
        }
    }
    peerIndex=newPeerIndex;
}
void Transmission::deletePeer(String address) {
  uint8_t intAddress[6];
  macAddressToIntArray(address, intAddress);
  deletePeer(intAddress);
}
void Transmission::initTransmission() {
  
  WiFi.mode(WIFI_STA);
  myStrAddress = WiFi.macAddress();
  Serial.println(myStrAddress);
  //write the mac address in right format (int tab)
  macAddressToIntArray(myStrAddress, myAdress);
  
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //add broadcast peer
  //uint8_t broad0[6] = {0,0,0,0,0,0};
  //registerPeer(broad0);

  //add broadcast peer
  esp_now_peer_info_t peerInfo = {};
  //peerInfo.ifidx=WIFI_IF_AP;
  uint8_t address[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  memcpy(peerInfo.peer_addr, address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
    
    // Add peer       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  
}
void Transmission::send(uint8_t address[], uint8_t* message, uint8_t len) {
    esp_err_t result = esp_now_send(address, message, len);
    if (result == ESP_OK) {
      //Serial.println("sended ok");
    }
    else {
      //Serial.println("Error sending the data");
    }
    delay(3);
}
void Transmission::broadcastAll(uint8_t* message, uint8_t len) {
  uint8_t broad[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  send(broad, message, len);
}

void Transmission::sendAll(uint8_t* message, uint8_t len) {
  for(uint8_t i = 0;i<peerIndex;i++) {
    send(peerAdresses[i], message, len);
    delayMicroseconds(2500);
  }
}
/*
void Transmission::sendModules(FieldTransmission modules){
  //sendAll((uint8_t*)&modules, sizeof(modules));
  broadcastAll((uint8_t*)&modules, sizeof(modules));
  delayMicroseconds(500);
}*/





void Transmission::OnDataSent(void (*callBack)(const unsigned char*, esp_now_send_status_t)){
  esp_now_register_send_cb(*callBack);
}
void Transmission::OnDataRecv(void (*callBack)(const unsigned char*, const unsigned char*, int)){
  esp_now_register_recv_cb(*callBack);
}




void Transmission::setup(RobotData robotData) {
  #ifdef TARGET_X86
    WiFi.setup(robotData);
  #endif
}
