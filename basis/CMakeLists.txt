project(basis)

set(BASIS_LIB_HEADERS_DIR include)

set(BASIS_LIB_SRC_DIR src)

include_directories(${BASIS_LIB_HEADERS_DIR})

add_library(basis_lib SHARED ${BASIS_LIB_SRC_DIR}/igaFunctionSet.cpp
                        ${BASIS_LIB_SRC_DIR}/igaFunction.cpp)

target_link_libraries(basis_lib matrix_lib)

target_include_directories(basis_lib PUBLIC ${BASIS_LIB_HEADERS_DIR})