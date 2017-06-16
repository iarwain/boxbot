cmake_minimum_required(VERSION 2.6)

project(BoxBot)

include_directories("~/src/orx/code/include")
link_directories("~/src/orx/code/lib/dynamic")

set(CMAKE_CXX_STANDARD 11)

add_definitions(-D__orxDEBUG__)

set(SOURCE src/Game.cpp src/Player.cpp
    src/VirtualGamePad/orxVirtualGamePad.cpp
    src/VirtualGamePad/VirtualGamePadButton.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} orxd)