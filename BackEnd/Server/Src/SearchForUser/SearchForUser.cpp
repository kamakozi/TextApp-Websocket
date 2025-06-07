#include "SearchForUser/SearchForUser.h"
#include "DataBaseSingleton/DataBaseSingleton.h"

#include <pqxx/pqxx>
#include <iostream>
#include <vector>

std::vector<std::string> SearchForUser::getUser(const std::string& username) {
    std::vector<std::string> users;

    if (username.empty()) {
        return users;
    }

    try {
        pqxx::connection& conn = DataBaseSingleton::getInstance();
        pqxx::work xtn(conn);

        std::string Query = "SELECT username FROM users WHERE username ILIKE " + xtn.quote("%" + username + "%") + ";";
        pqxx::result result = xtn.exec(Query);

        for (const auto& row : result) {
            users.emplace_back(row["username"].c_str());
        }

        return users;

    } catch (const std::exception& e) {
        std::cerr << "Unable to search for user: " << e.what() << std::endl;
        return users;
    }
}