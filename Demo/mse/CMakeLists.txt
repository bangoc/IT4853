cmake_minimum_required(VERSION 3.0)
project(MSE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(thirdparty/googletest)
configure_file(resources/files.h.in resources/files.h)
add_executable(stick_tokenizer_ut stick_tokenizer_ut.cc stick_tokenizer.cc)
add_executable(intersect_ut intersect_ut.cc)

foreach (test_unit stick_tokenizer_ut intersect_ut)
  target_include_directories(${test_unit} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest/googletest/include)
  target_link_libraries(${test_unit} gtest gtest_main)
endforeach(test_unit)

add_executable(ld ld_main.cc inverted_index.cc conversions.cc token.cc
             index_reader.cc stick_tokenizer.cc vsm_query.cc index_constant.cc)

add_executable(indexer
    indexer.cc
    inverted_index.cc
    conversions.cc
    token.cc
    index_writer.cc
    files_iterator.cc
    stick_tokenizer.cc
    vsm_query.cc
    index_constant.cc )
target_link_libraries(indexer stdc++fs)

add_executable(searcher
    searcher.cc
    index_constant.cc
    inverted_index.cc
    conversions.cc
    token.cc
    stick_tokenizer.cc
    index_reader.cc
    query_parser.cc
    vsm_query.cc)
