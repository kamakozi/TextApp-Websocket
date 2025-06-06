//
// Created by ziga zoric on 06.06.25.
//
#include "../../Common/User.h"

#ifndef LOGINUSER_H
#define LOGINUSER_H
class LoginUser {
public:
    std::unique_ptr<User>loginUser(std::string username,std::string password);
};
#endif //LOGINUSER_H
