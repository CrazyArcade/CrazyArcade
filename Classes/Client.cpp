#include "Client.h"

USING_NS_CC;

bool Client::init()
{
    /// create ws instance
    ws = new network::WebSocket();
    if (!ws->init(*this, Settings::Sever::addr))
    {
        return false;
    }
    //this->

    return true;
}
