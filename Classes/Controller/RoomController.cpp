#include "RoomController.h"


bool RoomController::init()
{
    if (!Layer::init())
    {
        return false;
    }

    client = Client::getInstance();
    return true;
}

void RoomController::onEnter()
{
    Layer::onEnter();
    if (!client->isConnected())
    {
        client->connect();
    }
}
