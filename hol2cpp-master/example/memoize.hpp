#include <cstdint>
#include <cstdlib>
#include <map>
#include <memory>
#include <variant>

class snat {
    struct _sZero {
        bool operator<(const _sZero &) const { return false; }
    };
    struct _sSucc {
        std::shared_ptr<snat> p1_;

        snat p1() const { return *p1_; }

        bool operator<(const _sSucc &rhs) const {
            return std::tie(*p1_) < std::tie(*rhs.p1_);
        }
    };

    std::variant<_sZero, _sSucc> value_;
    snat(const std::variant<_sZero, _sSucc> &value) : value_(value) {}

  public:
    snat() = default;

    static snat sZero() {
        return snat { _sZero {  } };
    }
    static snat sSucc(const snat &p1) {
        return snat { _sSucc { std::make_shared<snat>(p1) } };
    }

    bool is_sZero() const { return std::holds_alternative<_sZero>(value_); }
    bool is_sSucc() const { return std::holds_alternative<_sSucc>(value_); }

    const _sSucc &as_sSucc() const { return std::get<_sSucc>(value_); }

    bool operator<(const snat &rhs) const { return value_ < rhs.value_; }
};

std::uint64_t fib(const std::uint64_t &arg1);

std::uint64_t fact(const std::uint64_t &arg1);

snat add(const snat &arg1, const snat &arg2);

snat sfib(const snat &arg1);

std::uint64_t natofsnat(const snat &arg1);

snat snatofnat(const std::uint64_t &arg1);

// generated by HOL2Cpp
