cmake_minimum_required(VERSION 3.3)
project(pong)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(pong
    Pong.cpp
    ball.cpp
    racket.cpp
    ball.hh
    racket.hh
)

target_link_libraries(pong
    ${OPENGL_LIBRARIES}
    glfw
)