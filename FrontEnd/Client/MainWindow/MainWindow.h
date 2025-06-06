//
// Created by ziga zoric on 06.06.25.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../../Common/User.h"

#include <QtWidgets/QWidget>



class MainWindow {
private:
    std::unique_ptr<User>user;
public:
    QWidget* mainWindow(std::unique_ptr<User> u);
};



#endif //MAINWINDOW_H
