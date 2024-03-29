#include "fact.ml.ud.hpp"

std::uint64_t fact(const std::uint64_t &arg1) {
    // fact 0 = 0
    if (arg1 == 0) {
        return 0;
    }

    // fact (Suc 0) = 1
    if (arg1 != 0) {
        if (arg1 - 1 == 0) {
            return 1;
        }
    }

    // fact n = n * (fact (n - 1))
    auto temp0 = arg1 - 1;
    return arg1 * fact(std::move(temp0));
}

std::uint64_t fact_mem(const std::uint64_t &arg1) {
    auto impl = [&]() -> std::uint64_t {
        // fact_mem 0 = 0
        if (arg1 == 0) {
            return 0;
        }

        // fact_mem (Suc 0) = 1
        if (arg1 != 0) {
            if (arg1 - 1 == 0) {
                return 1;
            }
        }

        // fact_mem n = n * (fact (n - 1))
        auto temp0 = arg1 - 1;
        return arg1 * fact(std::move(temp0));
    };

    static std::map<std::tuple<std::uint64_t>, std::uint64_t> cache;
    auto args = std::make_tuple(arg1);
    auto it = cache.find(args);
    return it != cache.end() ? it->second : (cache.emplace(std::move(args), impl()).first->second);
}

std::optional<std::uint64_t> find_if(std::deque<std::uint64_t> arg1, const std::function<bool(const std::uint64_t &)> &arg2) {
    // find_if [] pred = None
    if (arg1.empty()) {
        return std::optional<std::uint64_t>();
    }

    // find_if [x] pred = If (pred x) (Some x) None
    if (arg1.size() == 1) {
        auto x = arg1[0];
        std::optional<std::uint64_t> temp0;
        if (arg2(x)) {
            temp0 = std::make_optional<std::uint64_t>(x);
        } else {
            temp0 = std::optional<std::uint64_t>();
        }
        return temp0;
    }

    // find_if (x # xs) pred = If (pred x) (Some x) (find_if xs pred)
    if (arg1.size() >= 1) {
        auto x = arg1.front();
        arg1.erase(arg1.begin(), arg1.begin() + 1);
        auto xs = std::move(arg1);
        std::optional<std::uint64_t> temp0;
        if (arg2(x)) {
            temp0 = std::make_optional<std::uint64_t>(x);
        } else {
            auto temp1 = std::move(xs);
            auto temp2 = arg2;
            temp0 = find_if(std::move(temp1), std::move(temp2));
        }
        return temp0;
    } else { // auto-generated for -Wreturn-type
        std::abort();
    }
}

std::optional<std::uint64_t> find_fact(std::deque<std::uint64_t> arg1, const std::uint64_t &arg2) {
    // find_fact xs x = find_if xs (% y. ((fact y) = x))
    auto temp0 = std::move(arg1);
    std::function temp2 = [=] (const std::uint64_t &y) {
        auto temp3 = y;
        return fact(std::move(temp3)) == arg2;
    };
    auto temp1 = temp2;
    return find_if(std::move(temp0), std::move(temp1));
}

std::optional<std::uint64_t> find_fact_mem(std::deque<std::uint64_t> arg1, const std::uint64_t &arg2) {
    // find_fact_mem xs x = find_if xs (% y. ((fact_mem y) = x))
    auto temp0 = std::move(arg1);
    std::function temp2 = [=] (const std::uint64_t &y) {
        auto temp3 = y;
        return fact_mem(std::move(temp3)) == arg2;
    };
    auto temp1 = temp2;
    return find_if(std::move(temp0), std::move(temp1));
}

// generated by HOL2Cpp
