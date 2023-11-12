#include "handlerManager.h"

HandlerManager::HandlerManager(std::shared_ptr<Router> router)
{
    
    
}

void HandlerManager::handleRequest(Request *request)
{
    Logger::log("HandlerManager : choose the right handler");
    for(BaseHandler* handler : this->handlers_) {
        if(handler->canHandle(request)) {
            handler->handle(request);
        }
    }
    
}

void HandlerManager::addHandler(BaseHandler *handler)
{
    this->handlers_.push_back(handler);
}


