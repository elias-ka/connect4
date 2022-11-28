cmake_minimum_required(VERSION 3.8)

project(
	"connect4"
	VERSION 0.2.0
	DESCRIPTION "A connect four game"
	HOMEPAGE_URL "https://github.com/elias-ka/connect4"
	LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

include(FindSDL2)

add_executable(connect4 "src/main.cpp" "include/grid.hpp" "src/grid.cpp" "include/game.hpp" "src/game.cpp")

target_compile_features(connect4 PUBLIC cxx_std_20)

target_include_directories(connect4 PUBLIC "include/" ${SDL2_INCLUDE_DIRS})

target_link_libraries(connect4
	PRIVATE ${SDL2_LIBRARIES}
)