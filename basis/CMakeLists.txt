project(basis)

set(BASIS_LIB_HEADERS_DIR include tensor/include)

set(BASIS_LIB_SRC_DIR src)

include_directories(${BASIS_LIB_HEADERS_DIR})

add_library(basis_lib   ${BASIS_LIB_SRC_DIR}/igaFunctionSet.cpp
                        ${BASIS_LIB_SRC_DIR}/igaFunction.cpp
                        ${BASIS_LIB_SRC_DIR}/igaBasis.cpp
                        ${BASIS_LIB_SRC_DIR}/igaBoundary.cpp
                        )

target_link_libraries(basis_lib matrix_lib)

target_include_directories(basis_lib PUBLIC ${BASIS_LIB_HEADERS_DIR})

add_executable(basis_test test/test.cpp)
target_link_libraries(basis_test gtest_main basis_lib)
add_test(NAME basis_test COMMAND basis_test)