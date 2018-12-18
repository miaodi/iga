cmake_minimum_required(VERSION 3.0)

project(IGA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -pedantic -Wextra")
# set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)


# disable insource build
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not permitted. \n How to fix this:\n 1. Type \nmake cleancmake\nto remove garbage CMake files. \n\n 2. Please make a separate folder for building, otherwise typing \nmake\nthat will create a ./build folder and will compile in that folder. ")
endif()

message(" ██▓  ▄████  ▄▄▄       ██▓     ██▓ ▄▄▄▄   ")
message("▓██▒ ██▒ ▀█▒▒████▄    ▓██▒    ▓██▒▓█████▄ ")
message("▒██▒▒██░▄▄▄░▒██  ▀█▄  ▒██░    ▒██▒▒██▒ ▄██")
message("░██░░▓█  ██▓░██▄▄▄▄██ ▒██░    ░██░▒██░█▀  ")
message("░██░░▒▓███▀▒ ▓█   ▓██▒░██████▒░██░░▓█  ▀█▓")
message("░▓   ░▒   ▒  ▒▒   ▓▒█░░ ▒░▓  ░░▓  ░▒▓███▀▒")
message(" ▒ ░  ░   ░   ▒   ▒▒ ░░ ░ ▒  ░ ▒ ░▒░▒   ░ ")
message(" ▒ ░░ ░   ░   ░   ▒     ░ ░    ▒ ░ ░    ░ ")
message(" ░        ░       ░  ░    ░  ░ ░   ░      ")
message("                                        ░ ")

message("Cmake generator is set to ${CMAKE_GENERATOR}")

set(EIGEN_INC_DIR ${PROJECT_SOURCE_DIR}/deps/eigen)
set(CONFIGURATION_INC_DIR ${PROJECT_SOURCE_DIR}/configuration)
set(UTIL_INC_DIR ${PROJECT_SOURCE_DIR}/util)
message("Eigen is found in ${EIGEN_INC_DIR}")
set(IGA_INCLUDE_DIRS ${EIGEN_INC_DIR} ${CONFIGURATION_INC_DIR} ${UTIL_INC_DIR})

# find_package(OpenMP)
# if (OPENMP_FOUND)
#     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#     set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()

# include given directories to all target and subdirectories
include_directories(${IGA_INCLUDE_DIRS})

enable_testing()
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

add_subdirectory(matrix)

add_subdirectory(basis)

set(IGA_LIBS matrix_lib basis_lib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${IGA_LIBS})
