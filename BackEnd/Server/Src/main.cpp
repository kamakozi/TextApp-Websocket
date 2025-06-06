//
// Created by ziga zoric on 06.06.25.
//
#include "LoadTables/LoadTables.cpp"
#include <iostream>
int main(int argc,char *argv[]) {
    LoadTables lt;
    lt.loadTables();
    std::cout << "Back end starting" << std::endl;
    return 0;
}