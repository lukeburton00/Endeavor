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

if (WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:\\Dev\\SDL-release-2.26.2\\build\\install\\cmake")
    list(APPEND CMAKE_PREFIX_PATH "C:\\Dev\\vcpkg\\packages\\glm_x86-windows\\share\\glm")
    set(GLEW_INCLUDE_DIR "C:\\Dev\\glew-2.1.0\\include\\GL")
    set(GLEW_LIBRARIES "C:\\Dev\\glew-2.1.0\\lib\\Release\\x64\\glew32.lib")
    set(GLEW_SHAREDLIB "C:\\Dev\\glew-2.1.0\\bin\\Release\\x64\\glew32.dll")
    set(GLM_INCLUDE_DIRS "C:\\Dev\\vcpkg\\packages\\glm_x86-windows\\include\\glm")
    set(FREETYPE_INCLUDE_DIRS "C:\\Dev\\vcpkg\\packages\\freetype_x86-windows\\include")
    set(FREETYPE_LIBRARIES "C:\\Dev\\vcpkg\\packages\\freetype_x86-windows\\lib\\freetype.lib")

    find_package(GLM REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS} PRIVATE ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_LIBRARIES} PRIVATE ${FREETYPE_LIBRARIES})

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_SHAREDLIB} $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)

else()
    find_package(Freetype REQUIRED)
    find_package(GLEW REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)
endif()

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} 
PUBLIC src
PUBLIC external
PUBLIC ${FREETYPE_INCLUDE_DIRS} PUBLIC ${SDL2_INCLUDE_DIRS} 
PUBLIC ${GLEW_INCLUDE_DIR} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 PUBLIC ${OPENGL_LIBRARIES} PUBLIC ${FREETYPE_LIBRARIES})