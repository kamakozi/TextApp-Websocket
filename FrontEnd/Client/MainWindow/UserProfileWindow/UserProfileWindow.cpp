#include "UserProfileWindow.h"

#include <iostream>

#include "ChangeDeatils/ChangeDetails.h"
#include "../../Common/User.h"
#include "../MainWindow.h"


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <memory>
#include <__ostream/basic_ostream.h>

QWidget *UserProfileWindow::userProfileWindow(User& u) {
    QWidget* window = new QWidget;
    window->resize(1000, 700);
    window->setWindowTitle("Profile");
    window->setStyleSheet("background-color: #1e1e2e; color: white; font-family: 'Segoe UI';");

    std::cout << "Name: " << u.getUsername() << std::endl;

    QPixmap rawImg(100, 100);
    rawImg.fill(Qt::gray);

    QPixmap roundedImg(rawImg.size());
    roundedImg.fill(Qt::transparent);
    QPainter painter(&roundedImg);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(rawImg));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, rawImg.width(), rawImg.height());

    QLabel* profileImage = new QLabel;
    profileImage->setPixmap(roundedImg);
    profileImage->setFixedSize(100, 100);
    profileImage->setAlignment(Qt::AlignCenter);


    QLabel* userName = new QLabel(QString::fromStdString(u.getUsername()));
    userName->setStyleSheet("font-size: 24px; font-weight: bold;");
    userName->setAlignment(Qt::AlignCenter);


    QLabel* description = new QLabel("Bio or user description goes here...");
    description->setAlignment(Qt::AlignCenter);
    description->setStyleSheet("font-size: 14px; color: #bbbbbb;");


    QPushButton* changeDetails = new QPushButton("Change Details");
    QPushButton* logout = new QPushButton("Logout");
    QPushButton* backButton = new QPushButton("Back");

    QString buttonStyle =
        "QPushButton { background-color: #3a3a5a; color: white; border-radius: 12px; padding: 12px; font-size: 14px; }"
        "QPushButton:hover { background-color: #4a4a6a; }";

    changeDetails->setStyleSheet(buttonStyle);
    logout->setStyleSheet("QPushButton { background-color: #ff4d4d; color: white; border-radius: 12px; padding: 12px; font-size: 14px; } QPushButton:hover { background-color: #ff6666; }");

    changeDetails->setFixedWidth(200);
    logout->setFixedWidth(200);

    backButton->setStyleSheet(buttonStyle);

    QVBoxLayout* box_layout = new QVBoxLayout;
    box_layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    box_layout->setSpacing(20);
    box_layout->setContentsMargins(50, 50, 50, 50);

    box_layout->addWidget(profileImage);
    box_layout->addWidget(userName);
    box_layout->addWidget(description);
    box_layout->addSpacing(20);
    box_layout->addWidget(changeDetails);
    box_layout->addWidget(backButton);
    box_layout->addWidget(logout);

    QObject::connect(backButton, &QPushButton::clicked, [=, &u]() {
    MainWindow mw;
    QWidget* newWindow = mw.mainWindow(std::make_unique<User>(u));
    newWindow->show();
    window->close();
});

    QObject::connect(changeDetails, &QPushButton::clicked, [=] {
        ChangeDetails cd;
        QWidget* newWindow = cd.changeDetails(std::make_unique<User>(u));
        newWindow->show();
        window->close();
    });

    QObject::connect(logout, &QPushButton::clicked, [=] {
        window->close();

    });

    window->setLayout(box_layout);
    window->show();
    return window;
}
