cmake_minimum_required(VERSION 3.0.0)
project(ticks VERSION 0.1.0)

set(FILES
	src/main.cpp
	src/types.hpp
	src/types.cpp
	src/rules.hpp
	src/rules.cpp
	src/engine.hpp
	src/engine.cpp
	src/protocols/command_line.hpp
	src/protocols/command_line.cpp
)

add_executable(ticks ${FILES})
target_include_directories(ticks PRIVATE src)
