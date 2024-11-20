#pragma once

#define un_bin_op_decl(T, O, A)           \
T& operator A(const T& rhs);              \
friend T operator O (T lhs, const T& rhs)

#define bin_op_def(T, O, A)           \
T operator O (T lhs, const T& rhs) {  \
    lhs A rhs;                        \
    return lhs;                       \
}
