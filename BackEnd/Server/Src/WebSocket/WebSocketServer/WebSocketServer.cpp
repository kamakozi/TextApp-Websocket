#include "WebSocketServer.h"
#include <iostream>
#include <unistd.h>     // for close()
#include <cstring>      // for memset()
#include <netinet/in.h> // for sockaddr_in
#include <sys/socket.h> // for socket functions
#include <arpa/inet.h>  // for inet_ntoa()

WebSocketServer::WebSocketServer(int port) : port(port), webSocket(-1) {}

void WebSocketServer::start() {
    setupSocket();
    confirmConnection();
}

void WebSocketServer::setupSocket() {
    webSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (webSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    int opt = 1;
    setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(webSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(webSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(webSocket, 10) < 0) {
        perror("Listen failed");
        close(webSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << port << std::endl;
}