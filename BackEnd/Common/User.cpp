//
// Created by ziga zoric on 06.06.25.
//

#include "User.h"

#include <iostream>
User::User(std::string username, std::string password,std::string email, std::string role,std::string token):
username(std::move(username)),
password(std::move(password)),
email(std::move(email)),
role(std::move(role)),
token(std::move(token))
{};

User::User(const User& other)
    : username(other.username),
      password(other.password),
      email(other.email),
      role(other.role),
      token(other.token) {}

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

std::string User::getToken() const {
    return token;
}

void User::setUsername(const std::string &newUsername) {
    username = newUsername;
}

