//
// Created by ziga zoric on 07.06.25.
//

#ifndef CHANGEDETAILS_H
#define CHANGEDETAILS_H
#include "../../Common/User.h"

#include <QtWidgets/QWidget>



class ChangeDetails {
public:
    QWidget* changeDetails(std::unique_ptr<User>u);
};



#endif //CHANGEDETAILS_H
