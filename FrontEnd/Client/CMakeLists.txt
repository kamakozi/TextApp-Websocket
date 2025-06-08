cmake_minimum_required(VERSION 3.16)
project(ChatAppFrontend)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")

include_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/include")
link_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/lib")


include_directories("/opt/homebrew/include" "/usr/local/include")
link_directories("/opt/homebrew/lib" "/usr/local/lib")

find_package(Qt6 REQUIRED COMPONENTS Widgets WebSockets)


add_executable(ChatAppFrontend
        main.cpp
        LoginWindow/LoginWindow.cpp
        LoginWindow/LoginWindow.h
        RegisterWindow/RegisterWindow.cpp
        RegisterWindow/RegisterWindow.h
        MainWindow/MainWindow.cpp
        MainWindow/MainWindow.h
        ../../BackEnd/Server/Auth/RegisterUser/RegiterUser.cpp
        ../../BackEnd/Common/User.cpp
        MainWindow/UserProfileWindow/UserProfileWindow.cpp
        MainWindow/UserProfileWindow/UserProfileWindow.h
        MainWindow/UserProfileWindow/ChangeDeatils/ChangeDetails.cpp
        MainWindow/UserProfileWindow/ChangeDeatils/ChangeDetails.h )



target_include_directories(ChatAppFrontend
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../BackEnd/Common
        ${CMAKE_CURRENT_SOURCE_DIR}/../../BackEnd/Server/Include
        ${CMAKE_SOURCE_DIR}/BackEnd/Server/Src
        ${CMAKE_SOURCE_DIR}/BackEnd/Common
        ${CMAKE_SOURCE_DIR}/BackEnd/Server/Include

)
find_library(BCRYPT_LIB bcrypt PATHS /opt/homebrew/lib REQUIRED)

target_link_libraries(ChatAppFrontend
        PRIVATE
        websocketLib
        Qt6::Widgets
        ${BCRYPT_LIB}
        Qt6::WebSockets
        pqxx
        pq
)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "/opt/homebrew/lib;/opt/homebrew/opt/openssl@3/lib")
