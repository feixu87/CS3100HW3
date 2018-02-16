cmake_minimum_required (VERSION 3.0)
project (main)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS " -std=c++11 -O0 -g3 -Wall -Wextra ${CMAKE_CXX_FLAGS}")
endif()

add_executable(main
	clang.cpp
	clang.hpp
	filesystem.cpp
	filesystem.hpp
	process.cpp
	process.hpp
	
	main.cpp
)