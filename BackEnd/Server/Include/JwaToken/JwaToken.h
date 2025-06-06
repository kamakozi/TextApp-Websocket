//
// Created by ziga zoric on 07.06.25.
//

#ifndef JWATOKEN_H
#define JWATOKEN_H
#include <string>

class JwaToken {
public:
    std::string getToken(std::string& username);
};

#endif //JWATOKEN_H
