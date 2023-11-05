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
    this->con = client.get_connection(SERVER_URI, ec);
    if (ec) {
        std::cout << "> Connect initialization error: " << ec.message() << std::endl;
        return -1;
    }
    con->set_open_handler(websocketpp::lib::bind(
        &WebsocketInterface::onOpen,
        this, &client, websocketpp::lib::placeholders::_1
    ));
    con->set_fail_handler(websocketpp::lib::bind(
        &WebsocketInterface::onFail,
        this, &client, websocketpp::lib::placeholders::_1
    ));
    con->set_close_handler(websocketpp::lib::bind(
        &WebsocketInterface::onClose,
        this, &client, websocketpp::lib::placeholders::_1
    ));
    con->set_message_handler(websocketpp::lib::bind(
        &WebsocketInterface::onMessage, this, 
        websocketpp::lib::placeholders::_1, 
        websocketpp::lib::placeholders::_2
    ));

    client.connect(con);
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

void WebsocketInterface::send(std::string message)
{
    websocketpp::lib::error_code ec;
    if(isReady()) {
        client.send(con->get_handle(), message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cout << "> Error sending message: " << ec.message() << std::endl;
            return;
        }
    } 
}

void WebsocketInterface::onOpen(Client *c, ConnectionHandle hdl)
{
    status = ConnectionStatus::OPEN;
    ConnectionPtr con = c->get_con_from_hdl(hdl);
    server = con->get_response_header("Server");
}

void WebsocketInterface::onFail(Client *c, ConnectionHandle hdl)
{
    status = ConnectionStatus::FAIL;
    ConnectionPtr con = c->get_con_from_hdl(hdl);
    server = con->get_response_header("Server");
    error = con->get_ec().message();
}

void WebsocketInterface::onClose(Client *c, ConnectionHandle hdl)
{
    status = ConnectionStatus::CLOSE;
    ConnectionPtr con = c->get_con_from_hdl(hdl);
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " (" 
        << websocketpp::close::status::get_string(con->get_remote_close_code()) 
        << "), close reason: " << con->get_remote_close_reason();
    error = s.str();
}

void WebsocketInterface::onMessage(ConnectionHandle, Client::message_ptr msg)
{
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        for(HookFunction hook : hooks) {
            hook(msg->get_payload());
        }
    }
}

void WebsocketInterface::addHook(HookFunction newHook)
{
    this->hooks.push_back(newHook);
}

bool WebsocketInterface::isReady()
{
    return status == ConnectionStatus::OPEN;
}
