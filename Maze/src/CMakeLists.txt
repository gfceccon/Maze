include(${CMAKE_CURRENT_LIST_DIR}/util/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/framework/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/maze/CMakeLists.txt)

set(maze_SRC
	${util_SRC}
	${maze2_SRC}
	${framework_SRC}
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

