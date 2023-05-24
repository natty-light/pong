cmake_minimum_required(VERSION 3.3)
project(pong)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories("./external/freeglut")

add_executable(pong
    Pong.cpp
    ball.cpp
    racket.cpp
    ball.hh
    racket.hh
)

target_link_libraries(pong
    ${OPENGL_LIBRARY}
    GLUT
)