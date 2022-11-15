cmake_minimum_required(VERSION 3.8)

project(
	"connect4"
	VERSION 0.1.0
	DESCRIPTION "A command-line connect four game"
	HOMEPAGE_URL "https://github.com/elias-ka/connect4"
	LANGUAGES CXX
)

add_executable(connect4 "src/connect4.cpp")

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET connect4 PROPERTY CXX_STANDARD 20)
endif()

target_compile_features(connect4 PRIVATE cxx_std_20)