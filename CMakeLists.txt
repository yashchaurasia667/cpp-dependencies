cmake_minimum_required(VERSION 3.20)
project(GLRenderer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

# Include dirs
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3  REQUIRED)
find_package(glm    REQUIRED)
find_package(GLEW   REQUIRED)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    OpenGL::GL
    glfw
    glm::glm
    GLEW::GLEW
)

# Compile options
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic
  $<$<CONFIG:Release>:-O2>
  $<$<CONFIG:Debug>:-g -O0>
)
