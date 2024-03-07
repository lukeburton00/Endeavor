cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Endeavor)

set(SRC "endeavor/src/time/timer.cpp" 
"endeavor/src/math/random.cpp" "endeavor/src/math/noise/perlin_noise.cpp" 
"endeavor/src/renderer/camera.cpp" "endeavor/src/renderer/gl_element_buffer.cpp" "endeavor/src/renderer/gl_vertex_array.cpp" "endeavor/src/renderer/gl_vertex_buffer.cpp"
"endeavor/src/renderer/renderer.cpp" "endeavor/src/renderer/shader.cpp" "endeavor/src/renderer/texture.cpp"
"endeavor/vendor/stb/stb_image.cpp" "endeavor/src/core/game.cpp" "endeavor/src/core/window.cpp" "endeavor/src/core/input.cpp"
"endeavor/vendor/glad/src/glad.c")

add_library(${PROJECT_NAME} STATIC ${SRC})

add_subdirectory("endeavor/vendor/glfw")
add_subdirectory("endeavor/vendor/glm")

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} 
PUBLIC "endeavor/src"
PUBLIC "endeavor/vendor"
PUBLIC "endeavor/vendor/stb"
PUBLIC "endeavor/vendor/glm"
PUBLIC "endeavor/vendor/glad/include"
PUBLIC "endeavor/vendor/glfw/include"

PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} 
PRIVATE glfw PRIVATE 
${OPENGL_LIBRARIES} PRIVATE glm::glm)