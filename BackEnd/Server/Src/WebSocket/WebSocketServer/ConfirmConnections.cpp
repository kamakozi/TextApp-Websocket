//
// Created by ziga zoric on 07.06.25.
//
#include "WebSocketServer.h"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void WebSocketServer::confirmConnection() {
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        int clientSocket = accept(webSocket,(sockaddr*)&clientAddr,&clientLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        std::cout << "Client connected from " << inet_ntoa(clientAddr.sin_addr) << std::endl;

        close(clientSocket);
    }
}
