#pragma once

#include "cocos2d.h"
#include <string>

class Entity : public cocos2d::Node
{
public:
	Entity() = default;
	~Entity() = default;

	void setID(std::string);
	std::string getID() const;

	// virtual void setStatus();

private:
	std::string _id;
};