cmake_minimum_required(VERSION 3.25)
project(la)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(la
        src/main.cpp
        src/matrix.cpp
        src/columnVector.cpp
        src/utilities.cpp
        src/linearEquation.cpp
        src/LinearSystem.cpp
        src/polynomial.cpp)

enable_testing()

add_executable(
        matrix_tests
        tests/matrix_tests.cc
)
target_link_libraries(
        matrix_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_tests)