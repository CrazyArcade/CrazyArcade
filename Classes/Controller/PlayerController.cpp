#include "PlayerController.h"

USING_NS_CC;

bool PlayerController::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto listener = EventListenerCustom::create("on_local_player_move", [=](EventCustom* event)
    {
        char* buf = static_cast<char*>(event->getUserData());
        int mode;
        int direction;
        sscanf(buf, "%d %d", &mode, &direction);
        if (mode)
        {
            localPlayer->setDirection(static_cast<Player::Direction>(direction));
        }
        else
        {
            localPlayer->removeDirection(static_cast<Player::Direction>(direction));
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    scheduleUpdate();
    return true;
}

PlayerController::~PlayerController()
{

}

Player* PlayerController::createPlayer(const std::string& id, const std::string& role)
{
    auto player = Player::create(id, role);

    this->_playerList.pushBack(player);
    return player;
}

Player * PlayerController::createLocalPlayer(const std::string & id, const std::string & role)
{
    localPlayer = createPlayer(id, role);
    return localPlayer;
}

void PlayerController::setStatus(std::string id, Player::Status status)
{
    auto player = this->getPlayer(id);
    if (player)
    {
        player->setStatus(status);
    }
}

Player * PlayerController::getPlayer(std::string id)
{
    for (auto player : this->_playerList)
    {
        if (player->getID() == id)
        {
            return player;
        }
    }
    return nullptr;
}

void PlayerController::update(float dt)
{
    if (localPlayer) localPlayer->move();
}
