#include "LoginWindow.h"
#include "../RegisterWindow/RegisterWindow.h"
#include "LoginUser/LoginUser.h"
#include "../MainWindow/MainWindow.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QDebug>
#include <QMessageBox>

QWidget* LoginWindow::loginWindow() {

    auto* window = new QWidget;
    window->setFixedSize(500, 400);
    window->setStyleSheet("background-color: #1e1e2f; color: #ddd; font-family: 'Segoe UI';");


    auto* fade = new QGraphicsOpacityEffect(window);
    window->setGraphicsEffect(fade);
    auto* animation = new QPropertyAnimation(fade, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);


    auto* layout = new QVBoxLayout(window);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);

    auto* title = new QLabel("Welcome to TextApp");
    title->setStyleSheet("font-size: 24px; font-weight: 600;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);


    auto* usernameInput = new QLineEdit;
    usernameInput->setPlaceholderText("Username");
    usernameInput->setMinimumHeight(36);
    usernameInput->setStyleSheet(
        "QLineEdit { background-color: #2b2b3c; border-radius: 8px; padding: 10px; font-size: 14px; border: 1px solid #444; }"
        "QLineEdit:focus { border: 1px solid #0078d7; }"
    );


    auto* passwordInput = new QLineEdit;
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(36);
    passwordInput->setStyleSheet(
        "QLineEdit { background-color: #2b2b3c; border-radius: 8px; padding: 10px; font-size: 14px; border: 1px solid #444; }"
        "QLineEdit:focus { border: 1px solid #0078d7; }"
    );

    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);


    auto* loginBtn = new QPushButton("Login");
    loginBtn->setMinimumHeight(40);
    loginBtn->setStyleSheet(
        "QPushButton { background-color: #0078d7; color: white; font-weight: bold; border-radius: 6px; }"
        "QPushButton:hover { background-color: #005fa3; }"
    );
    layout->addWidget(loginBtn);


    auto* registerLayout = new QHBoxLayout;
    registerLayout->addStretch();

    auto* registerText = new QLabel("Don't have an account?");
    registerText->setStyleSheet("font-size: 13px;");

    auto* registerBtn = new QPushButton("Register");
    registerBtn->setStyleSheet(
        "QPushButton { background: transparent; color: #5ab0f7; border: none; font-weight: bold; }"
        "QPushButton:hover { text-decoration: underline; }"
    );

    registerLayout->addWidget(registerText);
    registerLayout->addWidget(registerBtn);
    registerLayout->addStretch();
    layout->addLayout(registerLayout);


    QObject::connect(loginBtn, &QPushButton::clicked, [=]() {
        qDebug() << "Login: " << usernameInput->text() << passwordInput->text();
    });

    QObject::connect(registerBtn, &QPushButton::clicked, [=]() {
        qDebug() << "Switch to Register screen!";
    });



    QObject::connect(loginBtn,&QPushButton::clicked,[=] {
        LoginUser lu;

        QString qname = usernameInput->text();
        QString qpass = passwordInput->text();


        MainWindow mw;
        auto newUser = lu.loginUser(qname.toStdString(),qpass.toStdString());
        if (newUser) {
            QMessageBox::information(window,"User found", "Login successful");
            QWidget* newWindow = mw.mainWindow(std::move(newUser));
            newWindow->show();
            window->close();
        }


    });

    QObject::connect(registerBtn,&QPushButton::clicked,[=] {
            RegisterWindow rw;
        QWidget* newWindow = rw.registerWindow();
        newWindow->show();
        window->close();

    });

    return window;
}