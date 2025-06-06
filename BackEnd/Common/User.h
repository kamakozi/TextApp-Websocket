//
// Created by ziga zoric on 06.06.25.
//

#ifndef USER_H
#define USER_H
#include <string>


class User {
protected:
    std::string username;
    std::string password;
    std::string email;
    std::string role;
    std::string token;
public:
    ~User();
    User(std::string username,std::string password,std::string email,std::string role,std::string token);
    [[nodiscard]] std::string getUsername()const;
    [[nodiscard]] std::string getPassword()const;
    [[nodiscard]] std::string getRole()const;
    [[nodiscard]] std::string getToken()const;
};



#endif //USER_H
