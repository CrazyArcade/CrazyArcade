#include "RoleBox.h"

bool RoleBox::init()
{
    return true;
}

void RoleBox::setRole(const std::string & role)
{
    this->role = role;
    // TODO 
}

std::string RoleBox::getRole()
{
    return role;
}
