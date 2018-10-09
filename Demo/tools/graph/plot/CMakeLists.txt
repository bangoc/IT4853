cmake_minimum_required(VERSION 3.0)
project(PRCombiner)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/include/python2.7)
add_executable(f combine2.cc)
target_link_libraries(f python2.7)

add_executable(pr pr.cc)
target_link_libraries(pr python2.7)

add_executable(hp hp.cc)
target_link_libraries(hp python2.7)

add_executable(heap heap.cc)
target_link_libraries(heap python2.7)

add_executable(heaplog heaplog.cc)
target_link_libraries(heaplog python2.7)

add_executable(zipf zipf.cc)
target_link_libraries(zipf python2.7)