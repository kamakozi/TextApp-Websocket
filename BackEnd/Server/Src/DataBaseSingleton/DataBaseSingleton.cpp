//
// Created by ziga zoric on 06.06.25.
//
#include "DataBaseSingleton/DataBaseSingleton.h"
#include "ReadEnvFile/ReadEnvFile.h"
#include <pqxx/pqxx>
#include <memory>
#include <fstream>
#include <iostream>
pqxx::connection& DataBaseSingleton::getInstance() {
    static std::unique_ptr<pqxx::connection>conn;

    ReadEnvFile ref;
    auto env = ref.readEnvFile();

    std::string stringBuilder = "dbname=" + env["DB_NAME"] +
                                " user=" + env["DB_USER"]+
                                " password=" + env["DB_PASSWORD"] +
                                " host=" + env["DB_HOST"] +
                                 " port=" + env["DB_PORT"];

    try{
        conn = std::make_unique<pqxx::connection>(stringBuilder);
        std::cout << "Singleton created!" << std::endl;
    }catch (std::exception& x) {
        std::cerr << "Unable to create singleton" << x.what() << std::endl;
    }

    return *conn;
}
