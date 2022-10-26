add_library(testLibrary
			src/ljgl.hpp
			src/glad/glad.c
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(testLibrary PUBLIC
	${OPENGL_LIBRARIES}
	glfw
	glm
	GL
	X11
	pthread
	Xrandr
	Xi
	dl
)

set_target_properties(testLibrary PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(testLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

