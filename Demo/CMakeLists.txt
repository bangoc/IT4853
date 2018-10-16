cmake_minimum_required(VERSION 3.0)
project(cran)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(cran tools/cran_parser.cc)
add_executable(file_iterator tools/file_iterator.cc)
target_link_libraries(file_iterator stdc++fs)
target_include_directories(file_iterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(pp intersection/positional/pp_intersect.cc)
