cmake_minimum_required(VERSION 3.8)

project(
	"connect4"
	VERSION 0.2.0
	DESCRIPTION "A connect four game"
	HOMEPAGE_URL "https://github.com/elias-ka/connect4"
	LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

find_package(SDL2 CONFIG REQUIRED)

add_executable(connect4 "src/main.cpp" "include/grid.hpp" "src/grid.cpp" "include/game.hpp" "src/game.cpp")

target_compile_features(connect4 PUBLIC cxx_std_20)

target_include_directories(connect4 PUBLIC "include/" "include/ai")

target_link_libraries(connect4
	PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)