cmake_minimum_required(VERSION 3.0)

project(IGA)

set(CMAKE_CXX_STANDARD 17)

message("Generator is set to ${CMAKE_GENERATOR}")

# disable insource build
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not permitted. \n How to fix this:\n 1. Type \nmake cleancmake\nto remove garbage CMake files. \n\n 2. Please make a separate folder for building, otherwise typing \nmake\nthat will create a ./build folder and will compile in that folder. ")
endif()


set(EIGEN_INC_DIR ${PROJECT_SOURCE_DIR}/deps/eigen)
message("Eigen is found in ${EIGEN_INC_DIR}")
set(IGA_INCLUDE_DIRS ${EIGEN_INC_DIR})
set(IGA_LIBS matrix_lib)
include_directories(${IGA_INCLUDE_DIRS})

add_subdirectory(matrix)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${IGA_LIBS})
