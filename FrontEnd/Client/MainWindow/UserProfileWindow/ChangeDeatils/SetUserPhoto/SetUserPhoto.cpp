//
// Created by ziga zoric on 07.06.25.
//

#include "SetUserPhoto.h"

#include <QtWidgets/QWidget>

QWidget* SetUserPhoto::setUserPhoto() {
    QWidget* popOutWindow = new QWidget;
    popOutWindow->resize(400,300);



    popOutWindow->show();

    return popOutWindow;

}
