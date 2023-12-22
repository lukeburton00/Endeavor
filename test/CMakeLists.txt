cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Test)

set(SRC "test_game.cpp")

add_executable(${PROJECT_NAME} ${SRC})

add_subdirectory(../endeavor build/endeavor)

target_include_directories(${PROJECT_NAME} PUBLIC ../endeavor)

target_link_libraries(${PROJECT_NAME} PUBLIC Endeavor)
