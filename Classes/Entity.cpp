#include "Entity.h"

void Entity::setID(std::string id)
{
	this->_id = id;
};

std::string Entity::getID() const
{
	return this->_id;
};