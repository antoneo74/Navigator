cmake_minimum_required(VERSION 3.10)

project(Graph)


add_library(${TARGET_GRAPH_LIB} STATIC ${LIB_GRAPH_SOURCE})
add_library(${TARGET_GRAPH_ALGORITM_LIB} STATIC ${LIB_GRAPH_ALGORITHM_SOURCE})

target_link_libraries(${TARGET_GRAPH_ALGORITM_LIB} ${TARGET_GRAPH_LIB})

set_target_properties(${TARGET_GRAPH_LIB} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(${TARGET_GRAPH_ALGORITM_LIB} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set_target_properties(${TARGET_GRAPH_LIB} PROPERTIES PREFIX "")
set_target_properties(${TARGET_GRAPH_ALGORITM_LIB} PROPERTIES PREFIX "")

target_include_directories(${TARGET_GRAPH_LIB} PUBLIC ${RELATIVE_HEADER_DIR})
target_include_directories(${TARGET_GRAPH_ALGORITM_LIB} PUBLIC ${RELATIVE_HEADER_DIR})
