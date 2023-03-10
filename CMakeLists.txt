cmake_minimum_required(VERSION 3.24)
project(GameLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameLife main.cpp src/Plate.cpp src/Plate.h src/common.h)

find_package(raylib QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git)
    FetchContent_MakeAvailable(raylib)
endif()
include_directories(${PROJECT_NAME} ${raylib_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
