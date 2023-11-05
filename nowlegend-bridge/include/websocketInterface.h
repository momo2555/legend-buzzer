#ifndef WEBSOCKET_INTERFACE_H
#define WEBSOCKET_INTERFACE_H

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <memory>

#define SERVER_URI "ws://localhost:2225"

using Client = websocketpp::client<websocketpp::config::asio_client>;
using ThreadPtr = std::shared_ptr<websocketpp::lib::thread>;
using ConnectionPtr = Client::connection_ptr;
using ConnectionHandle = websocketpp::connection_hdl;
using CloseCode =  websocketpp::close::status::value;

enum class ConnectionStatus {
    OPEN,
    CLOSE,
    FAIL,
};

class WebsocketInterface {
public:
    
    WebsocketInterface();
    ~WebsocketInterface();

    int connect ();
    void disconnect(CloseCode code, std::string reason);
    void send(std::string message);

    void onOpen(Client* c, ConnectionHandle hdl);
    void onFail(Client* c, ConnectionHandle hdl);
    void onClose(Client* c, ConnectionHandle hdl);
    void onMessage(Client* c, ConnectionHandle hdl);

    //void addHook(std::function newHook);
    bool isReady();

private:
    Client client {};
    ThreadPtr thread {};
    ConnectionPtr con {};
    ConnectionStatus status {ConnectionStatus::CLOSE};
    std::string server {"N/A"};
    std::string error {""};
    //std::vector<std::function> hooks {};

};

#endif