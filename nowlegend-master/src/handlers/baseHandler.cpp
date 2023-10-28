#include "baseHandler.h"

BaseHandler::BaseHandler(std::shared_ptr<RouterInterface> router)
{
    this->router_ = router;
}

void BaseHandler::handle(Request request)
{


}
