cmake_minimum_required(VERSION 3.8)

project(
	"connect4"
	VERSION 0.1.0
	DESCRIPTION "A command-line connect four game"
	HOMEPAGE_URL "https://github.com/elias-ka/connect4"
	LANGUAGES CXX
)

find_package(SDL2 CONFIG REQUIRED)

add_executable(connect4 "src/main.cpp" "include/grid.hpp" "src/grid.cpp" "include/game.hpp" "src/game.cpp")

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET connect4 PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(connect4 PUBLIC "include/")

target_link_libraries(connect4 
	PRIVATE 
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> 
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)