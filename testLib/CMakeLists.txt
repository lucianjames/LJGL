
add_library(testLibrary
			src/test.hpp
)

find_package(Curses REQUIRED)
target_link_libraries(testLibrary ncurses)

set_target_properties(testLibrary PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(testLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

