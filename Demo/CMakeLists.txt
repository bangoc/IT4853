cmake_minimum_required(VERSION 3.0)
project(cran)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(build_tools "Build the experimental tools" ON)
option(build_temporaries "Build the temporary executable" ON)

add_executable(cran cran_parser.cc)
add_subdirectory(thirdparty/googletest)
configure_file(algorithm/resources/files.h.in algorithm/resources/files.h)
foreach(test utilities_ut intersect_ut files_ut)
  add_executable(${test} algorithm/${test}.cc)
  target_include_directories(${test} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
  target_link_libraries(${test} gtest_main stdc++fs)
endforeach(test)

add_executable(listcv tools/list_converter.cc)
add_executable(dictionary_main structure/dictionary_main.cc structure/dictionary.cc)
target_include_directories(dictionary_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(intersect_main algorithm/intersect_main.cc)
target_include_directories(intersect_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (${build_tools})
  add_executable(file_iterator tools/file_iterator.cc)
  target_link_libraries(file_iterator stdc++fs)
  target_include_directories(file_iterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif (${build_tools})

if (${build_temporaries})
  add_executable(files_main algorithm/files_main.cc algorithm/files.cc structure/conversions.cc structure/token.cc)
  target_include_directories(files_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(files_main stdc++fs)
endif (${build_temporaries})

add_executable(pp intersection/positional/pp_intersect.cc)

set(IndexSRC structure/inverted_index.cc structure/conversions.cc structure/token.cc
             structure/postings.cc algorithm/files.cc structure/vsm_query.cc)

add_executable(indexer indexer.cc ${IndexSRC})
target_include_directories(indexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(indexer stdc++fs)

add_executable(ld ld_main.cc ${IndexSRC})
target_link_libraries(ld stdc++fs)

add_executable(searcher searcher.cc ${IndexSRC})
target_link_libraries(searcher stdc++fs)