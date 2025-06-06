# TextApp

TextApp is a modern, full-stack messaging application designed with a C++ backend and a Qt6-based frontend interface. It supports real-time communication via WebSockets, secure user registration and login, and PostgreSQL as the primary database system.

## Overview

This project aims to provide a modular, high-performance communication platform, suitable for desktop environments. The backend is implemented in C++ using modern practices such as CMake, libpqxx, and environment-based configuration management. The frontend is built with Qt6, offering a responsive and native user interface.

## Features

### Backend
- Built with modern C++ (C++17)
- CMake project structure for maintainability
- Secure database connection using PostgreSQL (libpqxx)
- Singleton pattern for managing database connections
- Environment variable management for credentials and configuration
- User registration and login handling (planned)
- Real-time messaging via WebSockets (planned)
- SQL schema auto-loading from `Tables.sql`

### Frontend
- Developed using Qt6 (Widgets and QML)
- User-friendly interface for authentication and chat
- Real-time updates and communication
- Plans for chat history, typing indicators, and user presence

## Technologies Used

- C++
- CMake
- libpqxx (PostgreSQL driver)
- Qt6 (Widgets and WebSockets)
- OpenSSL
- std::thread and memory-safe design patterns
- Docker (for database containerization)

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

Open the Qt project in Qt Creator or use:

```bash
cd FrontEnd/Client
mkdir build && cd build
cmake ..
make
./ChatAppFrontend
```

## Future Roadmap

- Implement secure password hashing (bcrypt)
- Add RESTful APIs as fallback for WebSocket communication
- Add logging and error reporting
- Integrate unit and integration tests
- Support for message persistence and offline notifications
- Improve frontend UX with QML animations and transitions

## License

This project is currently under development.
