//
// Created by ziga zoric on 06.06.25.
//

#include "LoadTables/LoadTables.h"
#include "DataBaseSingleton/DataBaseSingleton.h"

#include <fstream>
#include <iostream>
#include <pqxx/pqxx>

void LoadTables::loadTables() {

    std::ifstream readFile("/Users/zigazoric/Desktop/cpp/appchat/BackEnd/Sql/Tables.sql");
    if (!readFile) {
        std::cerr << "Unable to open file Tables.sql" << std::endl;
    }

    try{
    pqxx::connection& conn = DataBaseSingleton::getInstance();

        std::vector<std::string> statements;
        std::string line;
        while (std::getline(readFile, line, ';')) {
            std::string statement = line + ";";
            if (statement.find_first_not_of(" \t\n\r") != std::string::npos) {
                statements.push_back(statement);
            }
        }

        pqxx::work xtn(conn);

        for (auto& r : statements) {
            try{
            xtn.exec(r);
            }catch (std::exception& e) {
                std::cerr << "Unable to get tables from vector!" << e.what() << std::endl;
            }
        }
        xtn.commit();
        std::cout << "Tables created!" << std::endl;
    }catch (std::exception& e) {
        std::cerr << "Failed to load tables!" << std::endl;
    }

    std::cout << "All tables loaded!" << std::endl;
}

