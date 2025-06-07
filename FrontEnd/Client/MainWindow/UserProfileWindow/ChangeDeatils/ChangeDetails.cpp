#include "ChangeDetails.h"
#include "../../MainWindow.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

QWidget* ChangeDetails::changeDetails(std::unique_ptr<User> u) {
    QWidget* window = new QWidget;
    window->resize(1000, 700);
    window->setWindowTitle("Edit User");
    window->setStyleSheet("background-color: #1e1e2e; color: white; font-family: 'Segoe UI';");

    auto* layout = new QVBoxLayout(window);
    layout->setContentsMargins(100, 80, 100, 80);
    layout->setSpacing(20);

    auto* usernameLabel = new QLabel("Choose new username:");
    usernameLabel->setStyleSheet("font-size: 16px;");

    auto* editUsername = new QLineEdit;
    editUsername->setPlaceholderText("New username");
    editUsername->setStyleSheet("padding: 10px; border-radius: 8px; background-color: #2a2a3d; border: 1px solid #444;");

    auto* saveUsername = new QPushButton("Save Username");
    saveUsername->setStyleSheet("padding: 10px; background-color: #4a90e2; color: white; border: none; border-radius: 8px;");
    
    layout->addWidget(usernameLabel);
    layout->addWidget(editUsername);
    layout->addWidget(saveUsername);

    auto* passwordLabelOld = new QLabel("Old password:");
    passwordLabelOld->setStyleSheet("font-size: 16px;");

    auto* oldPassword = new QLineEdit;
    oldPassword->setPlaceholderText("Enter old password");
    oldPassword->setEchoMode(QLineEdit::Password);
    oldPassword->setStyleSheet("padding: 10px; border-radius: 8px; background-color: #2a2a3d; border: 1px solid #444;");

    auto* passwordLabelNew = new QLabel("New password:");
    passwordLabelNew->setStyleSheet("font-size: 16px;");

    auto* editPassword = new QLineEdit;
    editPassword->setPlaceholderText("Enter new password");
    editPassword->setEchoMode(QLineEdit::Password);
    editPassword->setStyleSheet("padding: 10px; border-radius: 8px; background-color: #2a2a3d; border: 1px solid #444;");

    auto* confirmPasswordLabel = new QLabel("Repeat new password:");
    confirmPasswordLabel->setStyleSheet("font-size: 16px;");

    auto* confirmPassword = new QLineEdit;
    confirmPassword->setPlaceholderText("Repeat password");
    confirmPassword->setEchoMode(QLineEdit::Password);
    confirmPassword->setStyleSheet("padding: 10px; border-radius: 8px; background-color: #2a2a3d; border: 1px solid #444;");

    auto* savePassword = new QPushButton("Save Password");
    savePassword->setStyleSheet("padding: 10px; background-color: #e94f4f; color: white; border: none; border-radius: 8px;");

    auto* backBtn = new QPushButton("Cancel");
    backBtn->setStyleSheet("padding: 10px; background-color: #808080; color: white; border: none; border-radius: 8px;");

    layout->addSpacing(30);
    layout->addWidget(passwordLabelOld);
    layout->addWidget(oldPassword);
    layout->addWidget(passwordLabelNew);
    layout->addWidget(editPassword);
    layout->addWidget(confirmPasswordLabel);
    layout->addWidget(confirmPassword);
    layout->addWidget(savePassword);
    layout->addWidget(backBtn);

    QObject::connect(backBtn,&QPushButton::clicked,[window,u = std::move(u)]()mutable {
        MainWindow mw;
        QWidget* newWindow = mw.mainWindow(std::move(u));
        newWindow->show();
        window->close();
    });

    window->setLayout(layout);
    window->show();
    return window;
}