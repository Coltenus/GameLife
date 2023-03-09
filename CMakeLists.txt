cmake_minimum_required(VERSION 3.24)
project(GameLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameLife main.cpp src/Plate.cpp src/Plate.h src/common.h)

find_package(raylib CONFIG REQUIRED)
include_directories(${PROJECT_NAME} ${raylib_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
