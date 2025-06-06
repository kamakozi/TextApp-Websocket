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
    std::string role;
public:
    ~User();
    User(std::string username,std::string password,std::string role);
    [[nodiscard]] std::string getUsername()const;
    [[nodiscard]] std::string getPassword()const;
    [[nodiscard]] std::string getRole()const;
};



#endif //USER_H
