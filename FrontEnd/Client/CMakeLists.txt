cmake_minimum_required(VERSION 3.16)
project(ChatAppFrontend)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt meta tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets WebSockets)

add_executable(ChatAppFrontend
        main.cpp

)

target_link_libraries(ChatAppFrontend
        PRIVATE
        Qt6::Widgets
        Qt6::WebSockets
)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "/opt/homebrew/lib;/opt/homebrew/opt/openssl@3/lib")
