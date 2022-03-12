#include <Err.h>
#include <utility>

namespace PasswordGuesstimator {
  auto err_in_val(const Err err, const uint64_t val) -> bool {
    if (err == Err::ERR_NONE && val != Err::ERR_NONE) return false;
    return (err & val) == err;
  }

  auto for_err(std::function<bool(const Err)> const &f) -> bool {
    for (auto err = static_cast<uint64_t>(Err::ERR_FIRST); err < static_cast<uint64_t>(Err::ERR_LAST); err = err == 0 ? 1 : err << 1) {
      if (!f(Err(err))) return false;
    }
    return true;
  }

  auto get_err_str(const uint64_t val) -> std::string {
    std::string err_str = "";
    auto append_to_err_str = [&err_str](std::string const& str) -> void {
      if (err_str == "") {
        err_str += str;
      } else {
        err_str += ", " + str;
      }
    };

    (void) for_err([&val, &err_str, &append_to_err_str](Err const err) -> bool {
      if (err_in_val(err, val)) {
        append_to_err_str(ERR_STR_MAP.at(err));
      }
      return true;
    });
    if (err_str.empty()) {
      err_str = ERR_STR_MAP.at(Err::ERR_NONE);
    }

    return err_str;
  }

  auto operator==(Err a, uint64_t b) -> uint64_t { return static_cast<uint64_t>(a) == b; }
  auto operator!=(Err a, uint64_t b) -> uint64_t { return static_cast<uint64_t>(a) != b; }
  auto operator<(Err a, uint64_t b)  -> uint64_t { return static_cast<uint64_t>(a) <  b; }
  auto operator>(Err a, uint64_t b)  -> uint64_t { return static_cast<uint64_t>(a) >  b; }
  auto operator<=(Err a, uint64_t b) -> uint64_t { return static_cast<uint64_t>(a) <= b; }
  auto operator>=(Err a, uint64_t b) -> uint64_t { return static_cast<uint64_t>(a) >= b; }
  auto operator==(uint64_t a, Err b) -> uint64_t { return a == static_cast<uint64_t>(b); }
  auto operator!=(uint64_t a, Err b) -> uint64_t { return a != static_cast<uint64_t>(b); }
  auto operator<(uint64_t a, Err b)  -> uint64_t { return a <  static_cast<uint64_t>(b); }
  auto operator>(uint64_t a, Err b)  -> uint64_t { return a >  static_cast<uint64_t>(b); }
  auto operator<=(uint64_t a, Err b) -> uint64_t { return a <= static_cast<uint64_t>(b); }
  auto operator>=(uint64_t a, Err b) -> uint64_t { return a >= static_cast<uint64_t>(b); }


  auto operator|(Err a, Err b)  -> uint64_t { return static_cast<uint64_t>(a) | static_cast<uint64_t>(b); }

  auto operator&(Err a, uint64_t b)  -> uint64_t { return static_cast<uint64_t>(a) & b; }
  auto operator|(Err a, uint64_t b)  -> uint64_t { return static_cast<uint64_t>(a) | b; }
  auto operator^(Err a, uint64_t b)  -> uint64_t { return static_cast<uint64_t>(a) ^ b; }
  auto operator<<(Err a, uint64_t b) -> uint64_t { return static_cast<uint64_t>(a) << b; }
  auto operator>>(Err a, uint64_t b) -> uint64_t { return static_cast<uint64_t>(a) >> b; }

  auto operator&(Err a, uint32_t b)  -> uint64_t { return static_cast<uint64_t>(a) & static_cast<uint64_t>(b); }
  auto operator|(Err a, uint32_t b)  -> uint64_t { return static_cast<uint64_t>(a) | static_cast<uint64_t>(b); }
  auto operator^(Err a, uint32_t b)  -> uint64_t { return static_cast<uint64_t>(a) ^ static_cast<uint64_t>(b); }
  auto operator<<(Err a, uint32_t b) -> uint64_t { return static_cast<uint64_t>(a) << static_cast<uint64_t>(b); }
  auto operator>>(Err a, uint32_t b) -> uint64_t { return static_cast<uint64_t>(a) >> static_cast<uint64_t>(b); }

  auto operator<<(std::ostream& os, const Err &err) -> std::ostream& {
    os << get_err_str(static_cast<uint64_t>(err));
    return os;
  }
} // namespace PasswordGuesstimator