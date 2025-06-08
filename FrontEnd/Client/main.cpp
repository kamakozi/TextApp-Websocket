//
// Created by ziga zoric on 06.06.25.
//

#include "LoginWindow/LoginWindow.h"


#include <QtWidgets/QWidget>
#include <QApplication>
#include <iostream>
int main(int argc,char *argv[]) {
    QApplication app(argc,argv);

    std::cout << "Front end loading.." << std::endl;
    LoginWindow lw;
    QWidget* window = lw.loginWindow();
    window->show();
     return app.exec();
}