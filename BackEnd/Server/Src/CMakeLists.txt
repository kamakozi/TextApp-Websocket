cmake_minimum_required(VERSION 3.16)
project(ChatAppServer)

set(CMAKE_CXX_STANDARD 17)


include_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/include")
link_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/lib")


include_directories("/opt/homebrew/include" "/usr/local/include")
link_directories("/opt/homebrew/lib" "/usr/local/lib")


find_package(OpenSSL REQUIRED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${CMAKE_SOURCE_DIR}/BackEnd/Libs/jwt-cpp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Libs/Jwt-cpp/include
)


add_library(websocketLib
        LoadTables/LoadTables.cpp
        ReadEnvFile/ReadEnvFile.cpp
        DataBaseSingleton/DataBaseSingleton.cpp
        ../Auth/PasswordHashing/PasswordHashing.cpp
        ../../Common/User.cpp
        ../Auth/LoginUser/LoginUser.cpp
        ../Auth/JwaToken/JwaToken.cpp

)

target_link_libraries(websocketLib
        PRIVATE OpenSSL::Crypto
)

target_include_directories(websocketLib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../Include
        include_directories(${CMAKE_SOURCE_DIR}/BackEnd/Libs/jwt-cpp/include)
)

add_executable(ChatAppServer
        main.cpp
)



target_link_libraries(ChatAppServer
        websocketLib
        ssl
        crypto
        z
        pqxx
        pq
        OpenSSL::Crypto
)


target_link_libraries(ChatAppServer websocketLib)


set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "/opt/homebrew/Cellar/libpqxx/7.10.1/lib;/opt/homebrew/opt/libpq/lib;/opt/homebrew/opt/openssl@3/lib")

