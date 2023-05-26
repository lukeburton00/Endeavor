cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(-DDEBUG)

project (Test VERSION 1)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(../endeavor ./endeavor/bin)
target_include_directories(${PROJECT_NAME} PUBLIC ../endeavor)
target_link_libraries(${PROJECT_NAME} PUBLIC Endeavor)