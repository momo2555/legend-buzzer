#include "handlers/handlerManager.h"

HandlerManager::HandlerManager(std::shared_ptr<RouterInterface> router)
{
    //init all handlers 
    this->initHandlers_();
}

void HandlerManager::handleRequest(Request request)
{
    
}

void HandlerManager::addHandler(BaseHandler handler)
{
    this->handlers_.push_back(handler);
}

void HandlerManager::initHandlers_()
{

}
