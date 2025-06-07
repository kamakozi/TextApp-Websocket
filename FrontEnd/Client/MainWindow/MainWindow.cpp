#include "MainWindow.h"
#include "SearchForUser/SearchForUser.h"

#include <QtWidgets>
#include <memory>


QWidget* MainWindow::mainWindow(std::unique_ptr<User> u) {
    user = std::move(u);

    QWidget* window = new QWidget;
    window->resize(1000, 700);
    window->setWindowTitle("AndroText");
    window->setStyleSheet("background-color: #1e1e2e; color: #f0f0f0; font-family: 'Segoe UI';");


    auto* mainLayout = new QVBoxLayout(window);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);


    auto* topBar = new QWidget;
    topBar->setFixedHeight(60);
    topBar->setStyleSheet("background-color: #2a2a3d;");
    auto* topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(20, 10, 20, 10);

    auto* searchBar = new QLineEdit;
    searchBar->setPlaceholderText("Search...");
    searchBar->setFixedHeight(40);
    searchBar->setStyleSheet(
        "QLineEdit { background-color: #3a3a5a; border-radius: 20px; padding: 10px 20px; font-size: 14px; border: 1px solid #444; }"
        "QLineEdit:focus { border: 1px solid #5ab0f7; }"
    );
    topLayout->addWidget(searchBar);

    auto* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    topLayout->addWidget(spacer);

    auto* menuBtn = new QPushButton("☰");
    menuBtn->setFixedSize(40, 40);
    menuBtn->setStyleSheet(
        "QPushButton { background-color: #3a3a5a; border-radius: 12px; font-size: 20px; color: white; }"
        "QPushButton:hover { background-color: #4a4a6a; }"
    );
    topLayout->addWidget(menuBtn);

    mainLayout->addWidget(topBar);


    auto* splitLayout = new QHBoxLayout;
    splitLayout->setContentsMargins(0, 0, 0, 0);
    splitLayout->setSpacing(0);

    auto* contactList = new QListWidget;
    contactList->setFixedWidth(320);
    contactList->setStyleSheet(
        "QListWidget { background-color: #252535; border: none; padding: 10px; }"
        "QListWidget::item { margin: 8px; padding: 16px; border-radius: 16px; background-color: #32324a; }"
        "QListWidget::item:selected { background-color: #45456a; }"
    );

    QStringList contacts = { "Emma", "John", "Ziga (You)", "Bot", "Mia", "Alex" };
    for (const auto& name : contacts)
        contactList->addItem(name);

    splitLayout->addWidget(contactList);


    auto* chatPlaceholder = new QLabel("← Select a contact to start chatting");
    chatPlaceholder->setAlignment(Qt::AlignCenter);
    chatPlaceholder->setStyleSheet("font-size: 20px; color: #888;");
    splitLayout->addWidget(chatPlaceholder);

    mainLayout->addLayout(splitLayout);


    auto* menuPanel = new QWidget(window);
    menuPanel->setFixedWidth(200);
    menuPanel->setStyleSheet("background-color: #2a2a3d; border-top-left-radius: 16px; border-bottom-left-radius: 16px;");
    menuPanel->move(window->width(), topBar->height());  // Initially hidden offscreen
    menuPanel->setVisible(false);

    auto* menuLayout = new QVBoxLayout(menuPanel);
    menuLayout->setContentsMargins(20, 30, 20, 20);
    menuLayout->addWidget(new QLabel("Profile"));
    menuLayout->addWidget(new QLabel("Settings"));
    menuLayout->addWidget(new QLabel("Logout"));


    QObject::connect(searchBar,&QLineEdit::textChanged,[=](const QString& text) {
        SearchForUser sfr;
        std::vector<std::string> result  = sfr.getUser(text.toStdString());
        contactList->clear();
        for (const auto& name : result) {
            contactList->addItem(QString::fromStdString(name));
        }
    });


    QObject::connect(menuBtn, &QPushButton::clicked, [=]() mutable {
        static bool isVisible = false;
        int endX = isVisible ? window->width() : window->width() - 200;
        menuPanel->setVisible(true);

        auto* anim = new QPropertyAnimation(menuPanel, "pos");
        anim->setDuration(300);
        anim->setStartValue(menuPanel->pos());
        anim->setEndValue(QPoint(endX, topBar->height()));
        anim->setEasingCurve(QEasingCurve::InOutQuad);
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        isVisible = !isVisible;
    });

    window->setLayout(mainLayout);
    window->show();
    return window;
}