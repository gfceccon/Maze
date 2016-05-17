include(${CMAKE_CURRENT_LIST_DIR}/core/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/model/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/shader/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/effects/CMakeLists.txt)

set(graphics_SRC
	${core_SRC}
	${model_SRC}
	${shader_SRC}
	${effects_SRC}
)
