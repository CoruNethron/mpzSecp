cmake_minimum_required(VERSION 3.0)
project(simpleMpzSecp)

set(CMAKE_CXX_STANDARD 11)

add_library(gmp STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(gmp PROPERTIES
        IMPORTED_LOCATION "/opt/homebrew/lib/libgmp.a"
        INTERFACE_INCLUDE_DIRECTORIES "/opt/homebrew/include/"
)

add_executable(simpleMpzSecp main.cpp)
target_link_libraries(simpleMpzSecp gmp)
