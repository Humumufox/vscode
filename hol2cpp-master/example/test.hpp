#include <cstdint>
#include <cstdlib>
#include <list>

template<typename T1>
std::uint64_t test(const std::list<T1> &arg1) {
    // test Nil = 0
    if (arg1.empty()) {
        return 0;
    }

    // test (Cons x xs) = length (If ((length xs) = 0) Nil xs) + 1
    auto xs = std::list<T1>(std::next(arg1.begin()), arg1.end());
    std::list<T1> temp0;
    if (xs.size() == 0) {
        temp0 = std::list<T1>();
    } else {
        temp0 = xs;
    }
    return temp0.size() + 1;
}

// generated by HOL2Cpp
