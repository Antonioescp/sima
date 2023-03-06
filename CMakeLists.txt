cmake_minimum_required(VERSION 3.20)

project(sima)

# Helps to set different compiler features such as language version
add_library(sima_compiler_features INTERFACE)

# Helps to set different options such as warning and optimization levels an so on
add_library(sima_compiler_options INTERFACE)

# Adding compiler features
target_compile_features(
    sima_compiler_features INTERFACE cxx_std_20 # Support for C++20
)

# Per compiler options
if(MSVC) # In case you are windows c++ compiler
  target_compile_options(
      sima_compiler_options INTERFACE 
        /Wall # Enabling all warnings
        /W4 # Raise warnings as errors
  )
elseif(CMAKE_COMPILER_IS_GNUCXX) # Any other compiler
  target_compile_options(
    sima_compiler_options
    INTERFACE 
        -pedantic # Disallow some compiler extensions
        -Wall # Enable most warnings
        -Wextra # Enable more warnings
        -Werror # Raise warnings as errors
        -g # Append debug information
        -O0 # do not optimize
    )
endif()


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

# Adding google test framework
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)
# List of tests to be included
list(APPEND Tests HelloWorldTest)

    enable_testing()
    include(GoogleTest)

# Adding every test file to build options, the test name in Tests must be the
# name of the file containing the code for the test
    foreach(name IN LISTS Tests)
        add_executable(${name} ${CMAKE_CURRENT_SOURCE_DIR}/test/${name}.cpp)
        target_link_libraries(${name} GTest::gtest_main)
        gtest_discover_tests(${name})
    endforeach()

endif()

# The sima library
add_library(sima STATIC include/sima/Vector2.hpp include/sima/Vector3.hpp
                        include/sima/Vector4.hpp include/sima/Concepts.hpp)
set_target_properties(sima PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(sima PUBLIC include)
target_link_libraries(sima PRIVATE sima_compiler_features sima_compiler_options)
