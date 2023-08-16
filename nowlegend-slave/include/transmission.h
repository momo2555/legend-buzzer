#ifndef _COM_H_
#define _COM_H_
#ifdef TARGET_ESP32
  #include <esp_now.h>
#endif

#include "WiFi.h"
#include "fct_utils.h"



  

  class Transmission {
      public:
          Transmission();
          void initTransmission();
          void registerPeer(uint8_t address[]);
          void deletePeer(uint8_t address[]);
          void registerPeer(String address);
          void deletePeer(String address);
          void OnDataSent(void (*callBack)(const unsigned char*, esp_now_send_status_t));
          void OnDataRecv(void (*callBack)(const unsigned char*, const unsigned char*, int));
          void send(uint8_t address[], uint8_t* message, uint8_t len);
          void sendAll(uint8_t* message, uint8_t len);
          

          void broadcastAll(uint8_t* message, uint8_t len);

          bool isNewMessage() {return newMessage;};
          uint8_t getPeerInex() {return peerIndex;};
          String getMyAddress(){return myStrAddress;};
          
         

          void setup(RobotData robotData);
          
          
      private:
          uint8_t myAdress[6];
          String myStrAddress;
          bool newMessage;
          String buffer;
          //uint8_t bufferIndex;
          //you cann add only 5 peers
          uint8_t peerAdresses[6][6];
          Withholding withholding[5];
          

          uint8_t peerIndex = 0;
          
          
          
  };




#endif
