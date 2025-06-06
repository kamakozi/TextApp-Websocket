//
// Created by ziga zoric on 06.06.25.
//

#include "LoginUser/LoginUser.h"
#include "DataBaseSingleton/DataBaseSingleton.h"
#include "PasswordHashing/PasswordHashing.h"
#include "../Libs/Jwt-cpp/include/jwt-cpp/jwt.h"
#include "JwaToken/JwaToken.h"

#include <iostream>
#include <bcrypt/BCrypt.hpp>
#include <pqxx/pqxx>


std::unique_ptr<User> LoginUser::loginUser(std::string username, std::string password) {
    try{
    pqxx::connection& conn = DataBaseSingleton::getInstance();

        pqxx::work xtn(conn);
        std::string getHashedPassword = "SELECT hashed_password,email FROM users WHERE username=" + xtn.quote(username);
        pqxx::result r = xtn.exec(getHashedPassword);
        if (r.empty()) {
            std::cout << "User not found!" << std::endl;
            return nullptr;
        }

        std::string storedHash = r[0]["hashed_password"].c_str();
        std::string storeEmail = r[0]["email"].c_str();

        if (BCrypt::validatePassword(password,storedHash)) {



            std::cout << "User found " << std::endl;

            JwaToken jt;
            std::string token = jt.getToken(username);

            std::string Query = "UPDATE users SET token = " + xtn.quote(token) +
                    " WHERE username = " + xtn.quote(username) +
                    " RETURNING token";
            pqxx::result re = xtn.exec(Query);
            if (re.empty()) {
                std::cout << "Cannot set jwa token to user" << std::endl;
            }
            std::string insertSession = "INSERT INTO session (user_id, refresh_token, expires_at) "
                            "VALUES ((SELECT id FROM users WHERE username = " + xtn.quote(username) + "), "
                            + xtn.quote(token) + ", NOW() + interval '7 days')";
            xtn.exec(insertSession);
            xtn.commit();

            return std::make_unique<User>(username,storedHash,storeEmail,"user",token);
        }else {
            std::cout << "Invalid credentials!" << std::endl;
            return nullptr;
        }


    }catch (std::exception& e) {
        std::cerr << "Unable to login! " << e.what() << std::endl;
        return nullptr;
    }
}
