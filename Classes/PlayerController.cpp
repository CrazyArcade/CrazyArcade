#include "PlayerController.h"

USING_NS_CC;

bool PlayerController::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

PlayerController::~PlayerController()
{

}

Player* PlayerController::createPlayer()
{
	auto player = new Player();
	// init

	this->_playerList.pushBack(player);
	return player;

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
