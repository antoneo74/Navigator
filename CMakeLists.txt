cmake_minimum_required(VERSION 3.14)

project(SimpleNavigator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

if(CMAKE_BUILD_TYPE MATCHES "^Debug")
  add_compile_options(-g -O0)
else()
  add_compile_options(-O0 -DNDEBUG)
endif()

# Libraries names
set(TARGET_GRAPH_LIB s21_graph)
set(TARGET_GRAPH_ALGORITM_LIB s21_graph_algorithms)

# Directories
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(LIBS_DIR ${SOURCE_DIR}/libs)
set(CONTROLLER_DIR ${SOURCE_DIR}/controller)
set(MODEL_DIR ${SOURCE_DIR}/model)
set(VIEW_DIR ${SOURCE_DIR}/view)
set(TESTS_DIR ${BASE_DIR}/tests)
set(ASSETS_DIR ${BASE_DIR}/assets)

set(RELATIVE_HEADER_DIR ${SOURCE_DIR})

# Sources
file(GLOB_RECURSE ALL_SOURCES ${SOURCE_DIR}/*.cc ${SOURCE_DIR}/*.h)
file(GLOB_RECURSE CLI_SOURCE ${CONTROLLER_DIR}/*.cc ${VIEW_DIR}/*.cc ${BASE_DIR}/app.cc)
file(GLOB_RECURSE LIB_GRAPH_SOURCE ${MODEL_DIR}/s21_graph.cc)
file(GLOB_RECURSE LIB_GRAPH_ALGORITHM_SOURCE  ${MODEL_DIR}/s21_graph_algorithms.cc
                                              ${MODEL_DIR}/traveling_salesman/*.cc
)
file(GLOB_RECURSE TEST_SOURCES ${TESTS_DIR}/*.cc)

add_executable(cli ${CLI_SOURCE})
target_link_libraries(cli ${TARGET_GRAPH_LIB})
target_link_libraries(cli ${TARGET_GRAPH_ALGORITM_LIB})

target_include_directories(cli PUBLIC ${RELATIVE_HEADER_DIR})

add_custom_target(format COMMAND clang-format --style=Google -i --verbose ${ALL_SOURCES})
add_custom_target(stylecheck COMMAND clang-format --style=Google -n --verbose ${ALL_SOURCES})
add_custom_target(cppcheck COMMAND cppcheck --language=c++ --enable=all --suppress=unusedFunction --suppress=missingInclude --inconclusive --suppress=functionStatic ${CLI_SOURCE} ${LIB_GRAPH_SOURCE} ${LIB_GRAPH_ALGORITHM_SOURCE})

enable_testing()
add_subdirectory(${MODEL_DIR})
add_subdirectory(${TESTS_DIR})