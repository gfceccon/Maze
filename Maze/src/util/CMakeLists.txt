include(${CMAKE_CURRENT_LIST_DIR}/glm/CMakeLists.txt)
set(util_SRC
	${CMAKE_CURRENT_LIST_DIR}/log.cpp
	${CMAKE_CURRENT_LIST_DIR}/color.cpp
	${glm_dummy}
	)
