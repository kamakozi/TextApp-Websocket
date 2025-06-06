#include "RegisterWindow.h"

#include <iostream>

#include "../LoginWindow/LoginWindow.h"
#include "../../../BackEnd/Server/Include/RegisterUser/RegisterUser.h"
#include "User.h"

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

QWidget* RegisterWindow::registerWindow() {
    auto* window = new QWidget;
    window->setFixedSize(500, 520);
    window->setStyleSheet("background-color: #1e1e2f; color: #ddd; font-family: 'Segoe UI';");
    window->setWindowTitle("Create a TextApp Account");


    auto* fade = new QGraphicsOpacityEffect(window);
    window->setGraphicsEffect(fade);
    auto* animation = new QPropertyAnimation(fade, "opacity");
    animation->setDuration(900);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    auto* layout = new QVBoxLayout(window);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);


    auto* title = new QLabel("Register for TextApp");
    title->setStyleSheet("font-size: 22px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);


    QLineEdit* usernameInput = new QLineEdit;
    usernameInput->setPlaceholderText("Username");
    
    QLineEdit* emailInput = new QLineEdit;
    emailInput->setPlaceholderText("Email");

    QLineEdit* passwordInput = new QLineEdit;
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    QLineEdit* confirmPasswordInput = new QLineEdit;
    confirmPasswordInput->setPlaceholderText("Confirm Password");
    confirmPasswordInput->setEchoMode(QLineEdit::Password);

    QList<QLineEdit*> fields = { usernameInput, emailInput, passwordInput, confirmPasswordInput };
    for (auto* field : fields) {
        field->setMinimumHeight(36);
        field->setStyleSheet(
            "QLineEdit { background-color: #2b2b3c; border-radius: 8px; padding: 10px; font-size: 14px; border: 1px solid #444; }"
            "QLineEdit:focus { border: 1px solid #0078d7; }"
        );
        layout->addWidget(field);
    }


    QPushButton* registerBtn = new QPushButton("Create Account");
    registerBtn->setMinimumHeight(40);
    registerBtn->setStyleSheet(
        "QPushButton { background-color: #28a745; color: white; font-weight: bold; border-radius: 6px; }"
        "QPushButton:hover { background-color: #218838; }"
    );
    layout->addWidget(registerBtn);


    auto* loginLayout = new QHBoxLayout;
    loginLayout->addStretch();

    auto* loginText = new QLabel("Already have an account?");
    loginText->setStyleSheet("font-size: 13px;");

    auto* loginBtn = new QPushButton("Log in");
    loginBtn->setStyleSheet(
        "QPushButton { background: transparent; color: #5ab0f7; border: none; font-weight: bold; }"
        "QPushButton:hover { text-decoration: underline; }"
    );

    loginLayout->addWidget(loginText);
    loginLayout->addWidget(loginBtn);
    loginLayout->addStretch();
    layout->addLayout(loginLayout);


    QObject::connect(registerBtn, &QPushButton::clicked, [=]() {

        QString username = usernameInput->text().trimmed();
        QString password = passwordInput->text();
        QString confirmPassword = confirmPasswordInput->text();
        QString email = emailInput->text().trimmed();


        if (password != confirmPassword || password.size() < 6) {
            QMessageBox::information(window,"Unmatched password!/Weak password", "Password must match!\nPassword can't be empty!");
            return window;
        }

        if (username.isEmpty()) {
            QMessageBox::information(window,"Username error","Username can't be empty");
            return window;
        }

        if (email.isEmpty() && email.contains('@') && email.contains('.')) {
            QMessageBox::information(window,"Invalid email","Please enter a valid email");
            return window;
        }
        RegisterUser ru;
        auto user = ru.createUser(username.toStdString(),password.toStdString(),email.toStdString());

        if (user) {
            std::cout << "Registered" << std::endl;
        }
        return window;
    });

    QObject::connect(loginBtn, &QPushButton::clicked, [=]() {
        LoginWindow lw;
        QWidget* newWindow = lw.loginWindow();
        newWindow->show();
        window->close();
    });

    return window;
}