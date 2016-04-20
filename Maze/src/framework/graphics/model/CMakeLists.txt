include(${CMAKE_CURRENT_LIST_DIR}/primitive/CMakeLists.txt)

set(model_SRC
	${CMAKE_CURRENT_LIST_DIR}/simple_model.cpp
	${primitive_SRC}
	)
