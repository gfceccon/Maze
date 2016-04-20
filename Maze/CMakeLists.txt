cmake_minimum_required(VERSION 3.4)
project(scramble)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lGL -lglfw -lGLEW -lX11 -lpthread -lXrandr -lXi -g -Wall")

include(src/CMakeLists.txt)
set(SOURCE_FILES
	${maze_SRC}
	)

add_executable(main ${SOURCE_FILES})
