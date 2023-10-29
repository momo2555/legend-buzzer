#include "handlers/echoHandler.h"

void EchoHandler::handle(Request *request)
{

}

bool canHandle(Request *request) 
{
    return request->getType() == RequestType::ECHO;
    
}