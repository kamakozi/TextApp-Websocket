//
// Created by ziga zoric on 06.06.25.
//

#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include "../../Common/User.h"
#include <memory>

class RegisterUser {
public:
    std::unique_ptr<User>createUser(std::string username,std::string password,std::string email);
};

#endif //REGISTERUSER_H
