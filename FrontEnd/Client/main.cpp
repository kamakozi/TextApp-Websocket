//
// Created by ziga zoric on 06.06.25.
//

#include "LoginWindow/LoginWindow.h"

#include <QtWidgets/QWidget>
#include <QApplication>
int main(int argc,char *argv[]) {
    LoginWindow lw;
    QApplication app(argc,argv);
    QWidget* window = lw.loginWindow();
    window->show();
     return app.exec();
}