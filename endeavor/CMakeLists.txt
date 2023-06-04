cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Endeavor)

set(SRC 
src/input/input.cpp src/time/time.cpp 
src/math/random.cpp src/math/noise/perlin_noise.cpp
src/graphics/asset_manager.cpp
src/graphics/sprite_batch.cpp
src/graphics/shader.cpp src/graphics/vao.cpp src/graphics/texture_2d.cpp 
src/graphics/window.cpp  src/graphics/camera.cpp

vendor/stb_image.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

add_subdirectory(vendor/sdl2)
add_subdirectory(vendor/glew)
add_subdirectory(vendor/glm)

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} 
PUBLIC src
PUBLIC vendor
PUBLIC vendor/glm
PUBLIC vendor/glew/include
PUBLIC vendor/sdl2/include

PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} 
PRIVATE SDL2::SDL2-static PRIVATE libglew_static PRIVATE 
${OPENGL_LIBRARIES} glm::glm)