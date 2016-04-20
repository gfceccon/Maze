include(${CMAKE_CURRENT_LIST_DIR}/graphics/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/audio/CMakeLists.txt)

set(framework_SRC
	${CMAKE_CURRENT_LIST_DIR}/event.cpp
	${CMAKE_CURRENT_LIST_DIR}/game.cpp
	${CMAKE_CURRENT_LIST_DIR}/window.cpp
	${graphics_SRC}
	${audio_SRC}
)

