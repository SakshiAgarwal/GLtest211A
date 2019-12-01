
cmake_minimum_required(VERSION 3.12)
project(GLtestCS211A)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -framework GLUT -framework OpenGL")
set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
include_directories(${GLEW_H})

set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
link_libraries(${OPENGL} ${GLEW_LINK})

add_executable(GLtestCS211A main.cpp)