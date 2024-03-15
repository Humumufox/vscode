#include "fib.hpp"

std::uint64_t fib(const std::uint64_t &arg1) {
    // fib 0 = 1
    if (arg1 == 0) {
        return 1;
    }

    // fib (Suc 0) = 1
    if (arg1 != 0) {
        if (arg1 - 1 == 0) {
            return 1;
        }
    }

    // fib n = (fib (n - 1)) + (fib (n - 2))
    return fib(arg1 - 1) + fib(arg1 - 2);
}

std::uint64_t fib_mem(const std::uint64_t &arg1) {
    auto impl = [&]() -> std::uint64_t {
        // fib_mem 0 = 1
        if (arg1 == 0) {
            return 1;
        }

        // fib_mem (Suc 0) = 1
        if (arg1 != 0) {
            if (arg1 - 1 == 0) {
                return 1;
            }
        }

        // fib_mem n = (fib_mem (n - 1)) + (fib_mem (n - 2))
        return fib_mem(arg1 - 1) + fib_mem(arg1 - 2);
    };

    static std::map<std::tuple<std::uint64_t>, std::uint64_t> cache;
    auto args = std::make_tuple(arg1);
    auto it = cache.find(args);
    return it != cache.end() ? it->second : (cache.emplace(std::move(args), impl()).first->second);
}

// generated by HOL2Cpp