
cmake_minimum_required(VERSION 3.14)
project("ideal_cache")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ideal_cache.out src/main.cpp)
target_include_directories(ideal_cache.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tests tests/test.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(tests)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()
