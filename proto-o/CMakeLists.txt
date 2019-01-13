cmake_minimum_required(VERSION 2.8)

project(proto-o C)
message("HOME = ${CMAKE_HOME_DIRECTORY}")
include_directories( ${CMAKE_HOME_DIRECTORY}/Proc/include )

add_executable(proto-o main.c)
target_link_libraries(proto-o
				IF
				Proc
)

add_subdirectory(IF)
add_subdirectory(Proc)
