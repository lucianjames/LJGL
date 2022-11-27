add_library(LJGL
			src/ljgl.hpp
			src/glad/glad.c
)

find_package(OpenGL REQUIRED)
find_package(assimp)
add_subdirectory(glfw)
add_subdirectory(glm)

target_link_libraries(LJGL PUBLIC
	${OPENGL_LIBRARIES}
	glfw
	glm
)

set_target_properties(LJGL PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(LJGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
