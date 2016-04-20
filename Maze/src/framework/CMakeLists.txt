include(${CMAKE_CURRENT_LIST_DIR}/graphics/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/audio/CMakeLists.txt)

set(framework_SRC
	${CMAKE_CURRENT_LIST_DIR}/maze.cpp
	${CMAKE_CURRENT_LIST_DIR}/path.cpp
	${CMAKE_CURRENT_LIST_DIR}/path_light.cpp
	${CMAKE_CURRENT_LIST_DIR}/player.cpp
	${graphics_SRC}
	${audio_SRC}
)

