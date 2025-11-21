cmake_minimum_required(VERSION 3.14)
project(laba5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fdab60b14b31b89d3e8b0b.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(pmr_queue_demo
    main.cpp
    fixed_memory_resource.cpp
)

add_executable(pmr_queue_tests
    test_pmr_queue.cpp
    fixed_memory_resource.cpp
)

target_link_libraries(pmr_queue_tests
    gtest_main
    gmock
)

target_include_directories(pmr_queue_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(pmr_queue_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(pmr_queue_demo PRIVATE -Wall -Wextra)
target_compile_options(pmr_queue_tests PRIVATE -Wall -Wextra)