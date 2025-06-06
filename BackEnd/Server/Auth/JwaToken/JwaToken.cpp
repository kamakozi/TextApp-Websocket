//
// Created by ziga zoric on 07.06.25.
//

#include "JwaToken/JwaToken.h"
#include "../Libs/Jwt-cpp/include/jwt-cpp/jwt.h"
#include "ReadEnvFile/ReadEnvFile.h"

std::string JwaToken::getToken(std::string& username) {

    ReadEnvFile ref;
    auto envMap = ref.readEnvFile();

    std::string secret = envMap["JWA_SECRET"];


    auto token = jwt::create()
        .set_issuer("kama")
        .set_subject(username)
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(1))
        .sign(jwt::algorithm::hs256(secret));

    return token;
}

