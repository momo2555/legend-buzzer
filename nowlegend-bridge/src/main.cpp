#include <websocketInterface.h>
#include <serialportInterface.h>


#include <cstdlib>

#include <iostream>
#include <map>
#include <string>
#include <sstream>



int main() {
    bool exec = true;
    SerialportInterface::ptr serial = std::make_unique<SerialportInterface>(SerialportInterface());
    WebsocketInterface websocket;

    serial->connect();
    websocket.connect();

    if (!serial->isReady()) return 1;
    
    while (exec) {
        if (websocket.isReady()) {
            std::string content = serial->read();
            if(content != "") {
                std::cout << content << std::endl;
                websocket.send(content);
            }
            
        }
    }


    return 0; 
}