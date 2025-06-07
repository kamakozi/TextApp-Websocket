//
// Created by ziga zoric on 07.06.25.
//

#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

class WebSocketServer {
private:
    int port;
    int webSocket;
    void setupSocket();
    void confirmConnection();
public:
    WebSocketServer(int port);
    void start();
};

#endif //WEBSOCKETSERVER_H
