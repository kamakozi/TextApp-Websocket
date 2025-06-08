
# TextApp

TextApp is a modern, full-stack messaging application built in pure C++ with a Qt6 frontend and a WebSocket-based backend. It supports real-time communication, secure authentication, PostgreSQL integration, and modular architecture suitable for scalable desktop applications.

## Overview

This project demonstrates how C++ can be used to build a complete client-server chat platform using:
- Qt6 for UI
- libpqxx for PostgreSQL DB
- WebSockets for real-time messaging
- JWT for session security
- bcrypt for password hashing
- Modular architecture for future scalability

## Key Features

### Backend (C++17)
- Modular architecture with clean separation (Auth, WebSocket, UserProfile, etc.)
- PostgreSQL integration using libpqxx with prepared statements
- JWT-based authentication (jwt-cpp)
- Password hashing using bcrypt (OpenSSL-based)
- WebSocket Server implemented from scratch
  - Manual frame parsing
  - Client handler management
  - Real-time message broadcasting
- .env file support for secure configuration loading
- Multithreading support using std::thread for handling clients
- Singleton pattern for database connection manager
- User registration and login
- User profile editing (change username/password)
- User image upload support

### Frontend (Qt6)
- Native desktop UI using Qt Widgets
- Login and Register windows
- Profile section (change username/password and upload image)
- Communicates with backend via WebSocket
- Modular UI structure: LoginWindow, MainWindow, UserProfileWindow, etc.

## Technologies Used

- C++17
- Qt6 (Widgets)
- libpqxx (PostgreSQL)
- OpenSSL
- jwt-cpp
- bcrypt
- std::thread
- CMake
- Docker (PostgreSQL container)

## Build Instructions

### Backend

```bash
cd appchat
mkdir build && cd build
cmake ..
make
./BackEnd/Server/Src/ChatAppServer
```

### Frontend (Qt6)

Open the Qt project in Qt Creator or:

```bash
cd FrontEnd/Client
mkdir build && cd build
cmake ..
make
./ChatAppFrontend
```

### Run Both Frontend and Backend Together

```bash
cd build
./run_all
```

## Project Structure

```
appchat/
├── BackEnd/
│   ├── Server/
│   │   ├── Src/                  # All source files: WebSocket, Auth, DB, etc.
│   │   ├── Include/              # All headers
│   │   └── Libs/                 # jwt-cpp and other libs
│   └── Common/                   # Shared classes like User
├── FrontEnd/
│   └── Client/                   # Qt6 GUI
│       └── MainWindow/           # Includes UserProfile editing, photo, etc.
├── CMakeLists.txt
├── docker-compose.yml
└── database.env
```

## Future Roadmap

- Secure password hashing (done)
- JWT-based token system (done)
- Environment-based config (done)
- Unit and integration tests
- Message persistence
- Offline push or polling fallback
- Add/friend system
- RCS-style encryption
- Message delivery status (sent, delivered, seen)
- Add RESTful fallback for WebSocket API
- Improve frontend UX (transitions, themes, etc.)


This project is under development
