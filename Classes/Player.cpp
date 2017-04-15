#include "Player.h"

Player::Player()
{
	// load resources
}

void Player::setStatus(Player::Status status)
{
	this->_status = status;
}

const Player::Status Player::getStatus() const
{
	return this->_status;
}