project(matrix)

include_directories(${EIGEN_INC_DIR}
                    include)

set(MATRIX_SOURCES ${matrix_SOURCE_DIR}/src/)
set(MATRIX_LIB_SRC ${MATRIX_SOURCES}/igaMatrix.cpp)

add_library(matrix_lib ${MATRIX_LIB_SRC})