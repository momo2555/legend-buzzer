#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <functional>
#include <esp_now.h>
#include "WiFi.h"
#include "fct_utils.h"
#include "request.h"
#include "logger.h"

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
        using ptr = std::shared_ptr<Transmission>;
          Transmission();
          void initTransmission();
          void registerPeer(MacAddress address);
          void deletePeer(MacAddress address);
          void registerEchoPeer();
          void deleteEchoPeer();
          void OnDataSent(void (*callBack)(const unsigned char*, esp_now_send_status_t));
          template<class A>
          void OnDataRecv(A* class_ptr, void (A::* callBack)(const unsigned char*, const unsigned char*, int)) {
            
            setReceiveCallback(
              [class_ptr, callBack](const unsigned char*a, const unsigned char*b, int c) -> void
              {
                (class_ptr->*callBack)(a, b, c);
              }
            );

            esp_now_register_recv_cb(receiveCallbackWrapper);
          }
          void send(uint8_t address[], uint8_t* message, uint8_t len);
          void send(MacAddress address, Request* request, SendMethod mothod = SendMethod::SINGLE);
          void sendOnce(MacAddress address, Request* request, bool strict = false);
          void sendAll(uint8_t* message, uint8_t len);
          
          

          void broadcastAll(uint8_t* message, uint8_t len);
          static MacAddress getMyAddress();
          bool isPeerRegistered(MacAddress address);
          
          
      private:
          MacAddress myAddress;
        
  };




#endif
