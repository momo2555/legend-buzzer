#include "handlerManager.h"

HandlerManager::HandlerManager(std::shared_ptr<RouterInterface> router)
{
    
    
}

void HandlerManager::handleRequest(Request *request)
{
    Serial.println("HandlerMangaer : choose the right handler");
    for(BaseHandler* handler : this->handlers_) {
        Serial.println("HandlerMangaer : check Handler");
        if(handler->canHandle(request)) {
            handler->handle(request);
        }
    }
    
}

void HandlerManager::addHandler(BaseHandler *handler)
{
    this->handlers_.push_back(handler);
}


