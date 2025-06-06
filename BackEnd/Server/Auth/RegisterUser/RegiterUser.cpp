//
// Created by ziga zoric on 06.06.25.
//
#include "RegisterUser/RegisterUser.h"
#include "PasswordHashing/PasswordHashing.h"
#include "DataBaseSingleton/DataBaseSingleton.h"

#include <pqxx/pqxx>
#include <iostream>
#include "../../Common/User.h"

std::unique_ptr<User> RegisterUser::createUser(std::string username,std::string password,std::string email) {

    PasswordHashing ph;

    std::string hashedPassword = ph.getHashedPassword(password);

    try {
        pqxx::connection& conn = DataBaseSingleton::getInstance();
        pqxx::work xtn(conn);

        std::string Query = "INSERT INTO users (username,hashed_password,role_id,email) VALUES "
                            "(" + xtn.quote(username) + " , " +
                                  xtn.quote(hashedPassword) + " , " +
                                  xtn.quote(2) + " , " +
                                  xtn.quote(email) + ")";

        xtn.exec(Query);
        xtn.commit();

        return std::make_unique<User>(username,hashedPassword,email,"user","");
    }catch (std::exception& e) {
        std::cerr << "Unable to register user! " << e.what() << std::endl;
        return nullptr;
    }

}
