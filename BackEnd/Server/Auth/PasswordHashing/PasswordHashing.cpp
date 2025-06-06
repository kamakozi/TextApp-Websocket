//
// Created by ziga zoric on 06.06.25.
//

#include "PasswordHashing/PasswordHashing.h"

#include <bcrypt/BCrypt.hpp>
#include <string>

std::string PasswordHashing::getHashedPassword(const std::string &password) {

    std::string hashedPassword = BCrypt::generateHash(password);


    return hashedPassword;
}


