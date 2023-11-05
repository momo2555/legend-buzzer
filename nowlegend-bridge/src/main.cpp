#include <websocketInterface.h>
#include <serialportInterface.h>


#include <cstdlib>

#include <iostream>
#include <map>
#include <string>
#include <sstream>


int main() 
{
    bool exec = true;
    SerialportInterface::ptr serial = std::make_unique<SerialportInterface>(SerialportInterface());
    WebsocketInterface websocket;

    serial->connect();
    websocket.connect();

    websocket.addHook([&] (std::string msg) {
        serial->write(msg + "\n");
    });

    if (!serial->isReady()) return 1;
    
    while (exec) {
        if (websocket.isReady()) {
            std::string content = serial->read();
            if(content != "") {
                std::cout << content << std::endl;

                if(content.substr(0,1) == "R") //send only if the first char is an R
                    websocket.send(content.substr(1)); // do not send the first letter, only the JSON
            }
            
        }
    }


    return 0; 
}