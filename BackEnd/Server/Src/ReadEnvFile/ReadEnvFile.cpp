//
// Created by ziga zoric on 06.06.25.
//

#include "ReadEnvFile/ReadEnvFile.h"

#include <fstream>
#include <iostream>
std::unordered_map<std::string, std::string> ReadEnvFile::readEnvFile() {
    std::unordered_map<std::string,std::string>env;
    std::ifstream readFile("/Users/zigazoric/Desktop/cpp/appchat/database.env");
    if (!readFile) {
        std::cerr << "Unable to open database.env" << std::endl;
    }

    std::string line;
    while (getline(readFile,line)) {
        size_t pos = line.find("=");
        if (pos != std::string::npos) {
            std::string key = line.substr(0,pos);
            std::string value = line.substr(pos +1 );
            env[key] = value;
        }
    }

    return env;

}

