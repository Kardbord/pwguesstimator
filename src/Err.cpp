#include <Err.h>
#include <utility>

namespace PasswordGuesstimator {
  auto err_in_val(const Err err, const uint64_t val) -> bool {
    return (uint64_t(err) & val) == 0;
  }

  auto for_err(std::function<bool(const Err)> const &f) -> bool {
    for (auto err = uint64_t(Err::ERR_FIRST); err < uint32_t(Err::ERR_LAST); err = err << 1) {
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

} // namespace PasswordGuesstimator