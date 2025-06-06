//
// Created by ziga zoric on 06.06.25.
//

#include "User.h"

#include <iostream>
User::User(std::string username, std::string password,std::string email, std::string role):
username(std::move(username)),
password(std::move(password)),
email(std::move(email)),
role(std::move(role))
{};

User::~User() = default;

std::string User::getPassword() const {
    return password;
}
std::string User::getRole() const {
    return role;
}
std::string User::getUsername() const {
    return username;
}
