project(basis)

set(BASIS_LIB_HEADERS_DIR include)

set(BASIS_LIB_SRC_DIR src)

include_directories(${BASIS_LIB_HEADERS_DIR})

add_library(basis_lib ${BASIS_LIB_SRC_DIR}/igaFunctionSet.cpp)

target_link_libraries(basis_lib matrix_lib)

target_include_directories(basis_lib PUBLIC ${BASIS_LIB_HEADERS_DIR})