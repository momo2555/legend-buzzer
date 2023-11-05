#include "websocketInterface.h"

WebsocketInterface::WebsocketInterface()
{
     // Open an endpoint
    this->client.clear_access_channels(websocketpp::log::alevel::all);
    this->client.clear_error_channels(websocketpp::log::elevel::all);

    this->client.init_asio();
    this->client.start_perpetual();
    
    this->thread = std::make_shared<websocketpp::lib::thread>(&Client::run, &client);
}

WebsocketInterface::~WebsocketInterface()
{
    client.stop_perpetual();
    if(status == ConnectionStatus::OPEN) {
        std::cout << "> Closing connection " << std::endl;
        disconnect(websocketpp::close::status::going_away, "");
        thread->join();
    }
}

int WebsocketInterface::connect()
{
    //connect to the server
    websocketpp::lib::error_code ec;
    this->con = m_endpoint.get_connection(SERVER_URI, ec);
    if (ec) {
        std::cout << "> Connect initialization error: " << ec.message() << std::endl;
        return -1;
    }
    con->set_open_handler(WsLib::bind(
        &WebsocketInterface::onOpen,
        this, &client, WsLib::placeholders::_1
    ));
    con->set_fail_handler(WsLib::bind(
        &WebsocketInterface::onFail,
        this, &client, WsLib::placeholders::_1
    ));
    con->set_close_handler(WsLib::bind(
        &WebsocketInterface::onClose,
        this, &client, WsLib::placeholders::_1
    ));
    con->set_message_handler(WsLib::bind(
        &WebsocketInterface::onMessage,
        this, &client, WsLib::placeholders::_1
    ));

    client.connect(con);
    status = ConnectionStatus::OPEN;
    return 0;
}

void WebsocketInterface::disconnect(CloseCode code, std::string reason)
{
    websocketpp::lib::error_code ec;
    client.close(con->get_handle(), code, reason);
    if(ec) {
        std::cout << "> Error initiating close: " << ec.message() << std::endl;
    }
    status = ConnectionStatus::CLOSE;
}

void WebsocketInterface::onOpen(Client *c, ConnectionHandle hdl)
{
}

void WebsocketInterface::onFail(Client *c, ConnectionHandle hdl)
{
}

void WebsocketInterface::onClose(Client *c, ConnectionHandle hdl)
{
}

void WebsocketInterface::onMessage(Client *c, ConnectionHandle hdl)
{
}
