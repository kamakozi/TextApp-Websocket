#include "DataBaseSingleton/DataBaseSingleton.h"
#include "../Include/UserProfile/ChangeUserCredentials/ChangeUserCredentials.h"
#include "bcrypt/BCrypt.hpp"

#include <iostream>
#include <pqxx/pqxx>

std::string ChangeUserCredentials::changeUsername(std::string& newUsername,std::string& oldUsername) {
    try {
        pqxx::connection& conn = DataBaseSingleton::getInstance();
        pqxx::work txn(conn);


        std::string checkQuery = "SELECT id FROM users WHERE username = " + txn.quote(newUsername) + ";";
        pqxx::result checkResult = txn.exec(checkQuery);

        if (!checkResult.empty()) {
            std::cerr << "Username '" << newUsername << "' is already taken.\n";
            return "";
        }


        std::string getIdQuery = "SELECT id FROM users WHERE username = " + txn.quote(oldUsername) + ";";
        pqxx::result idResult = txn.exec(getIdQuery);

        if (idResult.empty()) {
            std::cerr << "Old username '" << oldUsername << "' not found.\n";
            return "";
        }

        int userId = idResult[0][0].as<int>();


        std::string updateQuery = "UPDATE users SET username = " + txn.quote(newUsername) +
                                  " WHERE id = " + txn.quote(userId) + ";";

        txn.exec(updateQuery);
        txn.commit();

        std::cout << "Username updated from '" << oldUsername << "' to '" << newUsername << "'.\n";
        return newUsername;

    } catch (const std::exception& e) {
        std::cerr << "Unable to change username: " << e.what() << std::endl;
        return "";
    }
}


std::string ChangeUserCredentials::changePassword(std::string &newPassword, std::string &oldPassword,std::string& username) {

    try {
    pqxx::connection& conn = DataBaseSingleton::getInstance();

        pqxx::work xtn(conn);

        std::string QueryPassword = "SELECT hashed_password FROM users WHERE username = " +xtn.quote(username);

       pqxx::result r = xtn.exec(QueryPassword);
        if (r.empty()) {
            std::cerr << "User not found!" << std::endl;
            return "";
        }

        std::string getPassword = r[0]["hashed_password"].c_str();

        if (!BCrypt::validatePassword(oldPassword,getPassword)) {
            std::cout << "Old Password (user input): " << oldPassword << std::endl;
            std::cout << "Stored Hashed Password: " << getPassword << std::endl;
            std::cerr << "Invalid password" << std::endl;
            return "";
        }

        std::string newHashedPassword = BCrypt::generateHash(newPassword);

        std::string changePassword = "UPDATE users SET hashed_password = " +xtn.quote(newHashedPassword) +
                                     " WHERE username = " + xtn.quote(username) + ";";

        xtn.exec(changePassword);
        xtn.commit();

        return newHashedPassword;

    }catch (std::exception& e) {
        std::cerr << "Unable to change password" << e.what() << std::endl;
    }
}
