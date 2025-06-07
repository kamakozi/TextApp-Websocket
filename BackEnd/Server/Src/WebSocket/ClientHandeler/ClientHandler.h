//
// Created by ziga zoric on 07.06.25.
//

#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <string>


class ClientHandler {
private:
    int clientSocket;

    std::string readRequest();
    std::string generateAcceptKey(const std::string& clientKey);
    void sendHandshakeResponse(const std::string& acceptKey);

public:
    explicit ClientHandler(int clientSocket);
    void handle();
};



#endif //CLIENTHANDLER_H
