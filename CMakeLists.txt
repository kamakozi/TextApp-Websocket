cmake_minimum_required(VERSION 3.31)
project(appchat)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(BackEnd/Server/Src)
add_subdirectory(FrontEnd/Client/)

add_custom_target(run_all
        COMMAND $<TARGET_FILE:ChatAppServer> &
        COMMAND $<TARGET_FILE:ChatAppFrontend>
        DEPENDS ChatAppServer ChatAppFrontend
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)