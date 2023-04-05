cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project (Life VERSION 0.1)

add_executable(${PROJECT_NAME} Life.cpp)
add_subdirectory(../Engine ./engine/bin)
target_include_directories(${PROJECT_NAME} PUBLIC Scripts)
target_link_libraries(${PROJECT_NAME} PUBLIC Engine)