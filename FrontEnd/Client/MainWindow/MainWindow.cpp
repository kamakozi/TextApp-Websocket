#include "MainWindow.h"
#include "SearchForUser/SearchForUser.h"
#include "UserProfileWindow/UserProfileWindow.h"

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
    contactList->setStyleSheet(R"(
        QListWidget {
            background-color: #1e1e2e;
            border: none;
            padding: 12px;
        }
        QListWidget::item {
            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,
                                              stop:0 #2e2e42, stop:1 #3a3a5a);
            color: white;
            margin: 8px;
            padding: 16px;
            border-radius: 16px;
            border: 1px solid #44475a;
        }
        QListWidget::item:hover {
            background-color: #4b4b6a;
        }
        QListWidget::item:selected {
            background-color: #5c5c7c;
            border: 1px solid #5ab0f7;
        }
    )");

    QStringList contacts = { "Alen", "Blaz", "Ziga (You)", "Bot", "Mia", "Alex" };
    for (const auto& name : contacts)
        contactList->addItem(name);

    splitLayout->addWidget(contactList);

    auto* chatPlaceholder = new QLabel("← Select a contact to start chatting");
    chatPlaceholder->setAlignment(Qt::AlignCenter);
    chatPlaceholder->setStyleSheet("font-size: 20px; color: #888;");
    splitLayout->addWidget(chatPlaceholder);

    mainLayout->addLayout(splitLayout);


    QPushButton* profileButton = new QPushButton("Profile");
    QPushButton* settingsButton = new QPushButton("Settings");
    QPushButton* logoutButton = new QPushButton("Logout");

    auto* menuPanel = new QWidget(window);
    menuPanel->setFixedWidth(200);
    menuPanel->setFixedHeight(window->height());
    menuPanel->setStyleSheet("background-color: #2a2a3d; border-top-left-radius: 16px; border-bottom-left-radius: 16px;");
    menuPanel->move(window->width(), topBar->height());
    menuPanel->setVisible(false);


    auto* menuLayout = new QVBoxLayout(menuPanel);
    menuLayout->setContentsMargins(20, 30, 20, 20);
    menuLayout->setSpacing(20);


    QString modernBtnStyle = R"(
    QPushButton {
        background-color: #3a3a5a;
        color: white;
        border-radius: 12px;
        padding: 10px 20px;
        font-size: 14px;
        text-align: left;
        min-height: 40px;
    }
    QPushButton:hover {
        background-color: #4a4a6a;
    }
)";

    profileButton->setStyleSheet(modernBtnStyle);
    settingsButton->setStyleSheet(modernBtnStyle);
    logoutButton->setStyleSheet(modernBtnStyle);

    menuLayout->addWidget(profileButton);
    menuLayout->addWidget(settingsButton);
    menuLayout->addWidget(logoutButton);
    menuLayout->addStretch();

    menuPanel->setLayout(menuLayout);
    menuPanel->raise();

    auto* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);
    shadow->setOffset(-2, 2);
    shadow->setColor(QColor(0, 0, 0, 120));
    menuPanel->setGraphicsEffect(shadow);

    QObject::connect(searchBar, &QLineEdit::textChanged, [=](const QString& text) {
        SearchForUser sfr;
        std::vector<std::string> result = sfr.getUser(text.toStdString());
        contactList->clear();

        if (result.empty()) {
            QListWidgetItem* item = new QListWidgetItem("No user found");
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::NoItemFlags);
            item->setBackground(QColor("#3a3a5a"));
            item->setForeground(QColor("gray"));
            contactList->addItem(item);
            return;
        }

        for (const auto& name : result) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(name));
            item->setSizeHint(QSize(0, 48));
            item->setBackground(QColor("#32324a"));
            item->setForeground(QColor("white"));
            contactList->addItem(item);
        }
    });

    bool* isMenuOpen = new bool(false);

    QObject::connect(menuBtn, &QPushButton::clicked, [=]() mutable {
        int y = topBar->height();
        int startX = *isMenuOpen ? window->width() - 200 : window->width();
        int endX   = *isMenuOpen ? window->width() : window->width() - 200;

        menuPanel->move(startX, y);

        auto* anim = new QPropertyAnimation(menuPanel, "pos");
        anim->setDuration(300);
        anim->setStartValue(QPoint(startX, y));
        anim->setEndValue(QPoint(endX, y));
        anim->setEasingCurve(QEasingCurve::InOutQuad);

        if (!*isMenuOpen)
            menuPanel->setVisible(true); // show when opening

        QObject::connect(anim, &QPropertyAnimation::finished, [=]() {
            if (*isMenuOpen)
                menuPanel->setVisible(false);
            *isMenuOpen = !*isMenuOpen;
        });

        anim->start(QAbstractAnimation::DeleteWhenStopped);
    });

    QObject::connect(profileButton,&QPushButton::clicked,[=] {
        UserProfileWindow upw;
        QWidget* newWindow = upw.userProfileWindow(*user);
        newWindow->show();
        window->close();
    });

    window->setLayout(mainLayout);
    window->show();
    return window;
}