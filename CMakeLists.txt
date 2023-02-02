cmake_minimum_required(VERSION 3.20)

project(sima)

# Just for testing purposes
add_executable(Demo src/demo/HelloWorld.cpp)

# Helps to set different compiler features such as language version
add_library(compiler_features INTERFACE)

# Helps to set different options such as warning and optimization levels an so on
add_library(compiler_options INTERFACE)

# Adding compiler features
target_compile_features(compiler_features INTERFACE
    cxx_std_20 # Support for C++20
)

# Per compiler options
IF( MSVC ) # In case you are windows c++ compiler
    target_compile_options(compiler_options INTERFACE
        /Wall # Enabling all warnings
        /W4 # Raise warnings as errors
    )
ELSEIF( CMAKE_COMPILER_IS_GNUCXX ) # Any other compiler
    target_compile_options(compiler_options INTERFACE
            -pedantic # Disallow some compiler extensions
            -Wall # Enable most warnings
            -Wextra # Enable more warnings
            -Werror # Raise warnings as errors
    )
ENDIF()

# Adding google test framework
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)

# List of tests to be included
list(APPEND Tests
    HelloWorldTest
)

enable_testing()
include(GoogleTest)

# Adding every test file to build options, the test name in Tests must be the name
# of the file containing the code for the test
foreach(name IN LISTS Tests)
    add_executable(${name} ${CMAKE_CURRENT_SOURCE_DIR}/test/${name}.cpp)
    target_link_libraries(${name} GTest::gtest_main)
    gtest_discover_tests(${name})
endforeach()

# The sima library
add_library(sima INTERFACE)
target_include_directories(sima INTERFACE
        CMAKE_CURRENT_SOURCE_DIR/src/include
)
target_link_libraries(sima INTERFACE
    compiler_features
    compiler_options
)

target_link_libraries(Demo PUBLIC
    sima
    compiler_features
    compiler_options
)