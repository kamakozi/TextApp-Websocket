//
// Created by ziga zoric on 06.06.25.
//
#include "LoadTables/LoadTables.cpp"
#include "WebSocket/WebSocketServer/WebSocketServer.h"
#include <iostream>
int main(int argc,char *argv[]) {
    LoadTables lt;
    lt.loadTables();

    WebSocketServer server(8080);
    server.start();
    std::cout << "Back end starting" << std::endl;
    return 0;
}