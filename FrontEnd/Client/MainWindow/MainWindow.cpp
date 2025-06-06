//
// Created by ziga zoric on 06.06.25.
//

#include "MainWindow.h"
#include <memory>
#include <QtWidgets/QWidget>

QWidget *MainWindow::mainWindow(std::unique_ptr<User>u) {
    user = std::move(u);
    QWidget* window = new QWidget;
    window->resize(600,500);
    window->setWindowTitle("AndroText");

    window->show();

    return window;
}
