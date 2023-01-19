cmake_minimum_required(VERSION 3.20)

project(Threading)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB source_list "*.cpp")

message("Configure targets:")

foreach(file_path ${source_list})
    cmake_path(GET file_path FILENAME filename)
    GET_FILENAME_COMPONENT(target ${filename} NAME_WE)
    add_executable(${target} ${filename})
    target_link_libraries(${target} pthread)
    message(${target})
endforeach()
