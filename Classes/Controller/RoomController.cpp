#include "RoomController.h"



RoomController::RoomController()
{
}


RoomController::~RoomController()
{
}

bool RoomController::init()
{
    if (!Layer::init())
    {
        return false;
    }

    client = Client::getInstance();
}

void RoomController::onEnter()
{
    Layer::onEnter();
    if (!client->isConnected())
    {
        client->connect();
    }
}
