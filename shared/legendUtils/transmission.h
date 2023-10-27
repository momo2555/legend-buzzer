#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <functional>
#include <esp_now.h>
#include "WiFi.h"
#include "fct_utils.h"
#include "request.h"


#ifndef MAX_CONNECTION
  #define MAX_CONNECTION 10
#endif

#define ECHO_BROADCAST_ADDR {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

  typedef std::function <void(const unsigned char*, const unsigned char*, int)> ReceiveCallback;
  static ReceiveCallback receiveCallback {};
  void receiveCallbackWrapper(const unsigned char* a, const unsigned char* b, int c);
  void setReceiveCallback(ReceiveCallback cb);

  enum SendMethod {
    SINGLE = 0,
    ALL_PEERED,
    BROADCAST,
  };

  class Transmission {
      public:
          Transmission();
          void initTransmission();
          void registerPeer(uint8_t address[]);
          void registerEchoPeer();
          void deleteEchoPeer();
          void deletePeer(uint8_t address[]);
          void registerPeer(std::string address);
          void deletePeer(std::string address);
          void OnDataSent(void (*callBack)(const unsigned char*, esp_now_send_status_t));
          template<class A>
          void OnDataRecv(A* class_ptr, void (A::* callBack)(const unsigned char*, const unsigned char*, int)) {
            
            setReceiveCallback(
              [class_ptr, callBack](const unsigned char*a, const unsigned char*b, int c) -> void
              {
                Serial.println("receive a new frame");
                (class_ptr->*callBack)(a, b, c);
              }
            );

            //esp_now_register_recv_cb(receiveCallbackWrapper);
            esp_now_register_recv_cb([](const unsigned char*a, const unsigned char*b, int c) {
              Serial.println("YO SENT !");
            });
          }
          void send(uint8_t address[], uint8_t* message, uint8_t len);
          void send(MacAddress address, Request* request, SendMethod mothod = SendMethod::SINGLE);
          void sendOnce(MacAddress address, Request* request, bool strict = false);
          void sendAll(uint8_t* message, uint8_t len);
          
          

          void broadcastAll(uint8_t* message, uint8_t len);

          bool isNewMessage() {return newMessage;};
          uint8_t getPeerInex() {return peerIndex;};
          std::string getMyAddress(){return myStrAddress;};
          bool isPeerRegistered(uint8_t address[]);
          
          
      private:
          uint8_t myAdress[6];
          std::string myStrAddress;
          bool newMessage;
          //you cann add only 4 peers
          uint8_t peerAdresses[MAX_CONNECTION][6];
          
          

          uint8_t peerIndex = 0;
          
          
          
  };




#endif
