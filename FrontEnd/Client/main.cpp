//
// Created by ziga zoric on 06.06.25.
//

#include "LoginWindow/LoginWindow.h"
#include "WebSocket/WebSocketServer/WebSocketServer.h"

#include <QtWidgets/QWidget>
#include <QApplication>
int main(int argc,char *argv[]) {
    WebSocketServer server(8080);
    server.start();

    LoginWindow lw;
    QApplication app(argc,argv);
    QWidget* window = lw.loginWindow();
    window->show();
     return app.exec();
}