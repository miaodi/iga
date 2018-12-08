project(matrix)

include_directories(${EIGEN_INC_DIR} ${CONFIGURATION_INC_DIR})

add_library(matrix_lib INTERFACE)
target_include_directories(matrix_lib INTERFACE include/)