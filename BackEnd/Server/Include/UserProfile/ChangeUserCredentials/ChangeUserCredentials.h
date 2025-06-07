//
// Created by ziga zoric on 07.06.25.
//

#ifndef CHANGEUSERCREDENTIALS_H
#define CHANGEUSERCREDENTIALS_H
#include <string>


class ChangeUserCredentials {
public:
    std::string changeUsername(std::string& newUsername,std::string& oldUsername);
    std::string changePassword(std::string& newPassword,std::string& oldPassword,std::string& username);
};

#endif //CHANGEUSERCREDENTIALS_H
