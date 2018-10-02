cmake_minimum_required(VERSION 3.0)
project(benchmark)
add_executable(intersect_benchmark naive.cc sorted.cc benchmark.cc data.cc)
target_link_libraries(intersect_benchmark benchmark pthread)
