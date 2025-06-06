
#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H
#include <pqxx/pqxx>

class DataBaseSingleton {
public:
    static pqxx::connection &getInstance();
};


#endif //DATABASESINGLETON_H
