#include "binary_search.ml.hpp"

std::optional<std::uint64_t> bs_ml(const std::uint64_t &arg1, std::list<std::uint64_t> arg2) {
    // bs_ml x [] = None
    if (arg2.empty()) {
        return std::optional<std::uint64_t>();
    }

    // bs_ml x [y] = If (x = y) (Some 0) None
    if (arg2.size() == 1) {
        auto y = *std::next(arg2.begin(), 0);
        std::optional<std::uint64_t> temp0;
        if (arg1 == y) {
            temp0 = std::make_optional<std::uint64_t>(0);
        } else {
            temp0 = std::optional<std::uint64_t>();
        }
        return temp0;
    }

    // bs_ml x ys = (let m = (length ys) div 2 in ...
    auto temp0 = arg2.size() / 2;
    auto m = temp0;
    auto temp2 = arg2;
    auto temp1 = *std::next(temp2.begin(), m);
    auto y = temp1;
    std::optional<std::uint64_t> temp3;
    if (y == arg1) {
        temp3 = std::make_optional<std::uint64_t>(m);
    } else {
        std::optional<std::uint64_t> temp4;
        if (y < arg1) {
            auto temp5 = ([&] {
                auto temp6 = arg1;
                auto temp8 = m + 1;
                auto temp9 = std::move(arg2);
                temp9.erase(temp9.begin(), std::next(temp9.begin(), temp8));
                auto temp7 = std::move(temp9);
                auto temp10 = bs_ml(std::move(temp6), std::move(temp7));

                // Some n \<Rightarrow> Some (m + n + 1)
                if (temp10.has_value()) {
                    auto n = temp10.value();
                    return std::make_optional<std::uint64_t>((m + n) + 1);
                }

                // None \<Rightarrow> None
                if (!temp10.has_value()) {
                    return std::optional<std::uint64_t>();
                } else { // auto-generated for -Wreturn-type
                    std::abort();
                }
            })();
            temp4 = temp5;
        } else {
            auto temp11 = arg1;
            auto temp13 = m;
            auto temp14 = std::move(arg2);
            temp14.erase(std::next(temp14.begin(), temp13), temp14.end());
            auto temp12 = std::move(temp14);
            temp4 = bs_ml(std::move(temp11), std::move(temp12));
        }
        temp3 = temp4;
    }
    return temp3;
}

// generated by HOL2Cpp
