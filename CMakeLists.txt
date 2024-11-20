cmake_minimum_required(VERSION 3.0)
project(simpleMpzSecp)

set(CMAKE_CXX_STANDARD 11)

add_library(gmp STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(gmp PROPERTIES
        IMPORTED_LOCATION "/opt/homebrew/lib/libgmp.a"
        INTERFACE_INCLUDE_DIRECTORIES "/opt/homebrew/include/"
)

set(SRC_DIR src)
set(HEADER_FILES ${SRC_DIR}/Utils.h ${SRC_DIR}/Mpz.h ${SRC_DIR}/Modnum.h)
set(SOURCES main.cpp ${SRC_DIR}/Mpz.cpp ${SRC_DIR}/Modnum.cpp ${HEADER_FILES})

add_executable(simpleMpzSecp ${SOURCES})
target_link_libraries(simpleMpzSecp gmp)
