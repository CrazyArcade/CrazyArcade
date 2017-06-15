#ifndef __MODEL_USER_H__
#define __MODEL_USER_H__


#include <string>

class User
{
public:
    User(User const &) = delete;
    void operator=(User const &) = delete;
    
    static User* getInstance()
    {
        static User INSTANCE;
        return &INSTANCE;
    }

    void setUID(const std::string & uid) { this->uid = uid; }
    std::string getUID() const { return uid; }

    void setName(const std::string& name) { this->name = name; };
    std::string getName() const { return name; };

private:
    User() {};

    std::string uid;
    std::string name;
};

#endif



