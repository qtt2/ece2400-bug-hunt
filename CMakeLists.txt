#=========================================================================
# CMake script for PA1
#=========================================================================
# Author: Tuan Ta
# Date  : Aug 2018

#-------------------------------------------------------------------------
# !!!!DO NOT TOUCH THE FOLLOWING CODE!!!!
#-------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)
enable_language(C)

# ctest configs
include(CTest)
enable_testing()

# Set a default build type if none was specified
set(default_build_type "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Flags for GCC
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g --coverage")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os")
option(TEST_COVERAGE "Coverage testing with gcov" OFF)

if(TEST_COVERAGE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
endif(TEST_COVERAGE)

# Path to this PA's source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# Include path to this PA's header files
include_directories(${SRC_DIR})

#-------------------------------------------------------------------------
# Prepares a list of testing targets for each implementation
#-------------------------------------------------------------------------

# Get source files
set(TEST     "dlist-basic-tests")
set(IMPL_SRC "${SRC_DIR}/dlist.c")
set(TEST_SRC "${TEST_DIR}/dlist-basic-tests.c")

# Add tests
add_executable(${TEST} ${TEST_SRC} ${IMPL_SRC})
target_link_libraries(${TEST} m)
add_test(${TEST} ${TEST})
add_custom_target("check-${TEST}"
                  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${TEST}")

# Add memcheck target for this test
set(MEMTEST_TARGET "memcheck")
set(MEMTEST_DUMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/memtest-logs/")
add_custom_target(${MEMTEST_TARGET}
                  COMMAND mkdir -p "memtest-logs"
                  COMMAND valgrind "--trace-children=yes"
                                   "--leak-check=full"
                                   "--error-exitcode=1"
                                   "--log-file=${MEMTEST_DUMP_DIR}/${TEST}.log"
                                   "--undef-value-errors=no"
                                   "${CMAKE_CURRENT_BINARY_DIR}/${TEST}"
                                   ">${MEMTEST_DUMP_DIR}/${TEST}.stdout"
                  DEPENDS ${TEST})

# Add a target to run all tests using ctest
add_custom_target(check
                  COMMAND echo "Running all unit tests ..."
                  COMMAND ctest "--timeout" "120"
                  DEPENDS ${TESTS})
