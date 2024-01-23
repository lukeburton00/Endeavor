cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Endeavor)

set(SRC "src/time/timer.cpp" 
"src/math/random.cpp" "src/math/noise/perlin_noise.cpp" 
"src/renderer/camera.cpp" "src/renderer/gl_element_buffer.cpp" "src/renderer/gl_vertex_array.cpp" "src/renderer/gl_vertex_buffer.cpp"
"src/renderer/renderer.cpp" "src/renderer/shader.cpp" "src/renderer/texture.cpp"
"vendor/stb/stb_image.cpp" "src/core/game.cpp" "src/core/window.cpp" "src/core/input.cpp"
"vendor/glad/src/glad.c")

add_library(${PROJECT_NAME} STATIC ${SRC})

add_subdirectory("vendor/glfw")
add_subdirectory("vendor/glm")

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} 
PUBLIC "src"
PUBLIC "vendor"
PUBLIC "vendor/stb"
PUBLIC "vendor/glm"
PUBLIC "vendor/glad/include"
PUBLIC "vendor/glfw/include"

PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} 
PRIVATE glfw PRIVATE 
${OPENGL_LIBRARIES} PRIVATE glm::glm)