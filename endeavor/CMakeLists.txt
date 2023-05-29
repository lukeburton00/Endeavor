cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Endeavor VERSION 0.2)

set(SRC 
src/input/input.cpp src/time/time.cpp 
src/math/random.cpp src/math/noise/perlin_noise.cpp
src/graphics/asset_manager.cpp
src/graphics/sprite_batch.cpp src/graphics/renderer.cpp 
src/graphics/shader.cpp src/graphics/vao.cpp src/graphics/texture_2d.cpp 
src/graphics/window.cpp 

vendor/stb_image.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} 
PUBLIC src
PUBLIC vendor
PUBLIC ${SDL2_INCLUDE_DIRS} 
PUBLIC ${GLEW_INCLUDE_DIR} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} 
PRIVATE SDL2::SDL2 PRIVATE GLEW::GLEW PRIVATE 
${OPENGL_LIBRARIES})