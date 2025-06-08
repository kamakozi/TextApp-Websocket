cmake_minimum_required(VERSION 3.31)
project(appchat)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(BackEnd/Server/Src)
add_subdirectory(FrontEnd/Client/)

add_custom_target(run_all
        COMMAND ${CMAKE_COMMAND} -E echo "Starting Backend..."
        COMMAND ./BackEnd/Server/Src/ChatAppServer &
        COMMAND ${CMAKE_COMMAND} -E sleep 1
        COMMAND ${CMAKE_COMMAND} -E echo "Starting Frontend..."
        COMMAND ./FrontEnd/Client/ChatAppFrontend
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ChatAppServer ChatAppFrontend
)