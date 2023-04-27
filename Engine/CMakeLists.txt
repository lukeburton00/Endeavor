cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Engine VERSION 0.1)

add_definitions(-DDEBUG)

add_library(${PROJECT_NAME} STATIC
src/application/application.cpp 
src/ecs/system/physicssystem.cpp src/ecs/system/rendersystem.cpp src/ecs/system/scriptsystem.cpp src/core/input/input.cpp
src/core/time/time.cpp src/core/math/random.cpp src/core/math/noise/perlinnoise.cpp
src/core/assetmanager.cpp src/scene/scene.cpp
src/graphics/renderer.cpp src/graphics/shader.cpp 
src/graphics/vao.cpp src/graphics/texture2d.cpp src/graphics/window.cpp 
src/graphics/spritebatcher/spritebatcher.cpp
external/stb_impl.cpp)

find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} 
PUBLIC src
PUBLIC external
PUBLIC ${FREETYPE_INCLUDE_DIRS} PUBLIC ${SDL2_INCLUDE_DIRS} 
PUBLIC ${GLEW_INCLUDE_DIR} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 PUBLIC GLEW::GLEW PUBLIC ${OPENGL_LIBRARIES} PUBLIC ${FREETYPE_LIBRARIES})