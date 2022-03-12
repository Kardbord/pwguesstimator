#ifndef GUESTIMATOR_ERR_H
#define GUESTIMATOR_ERR_H

#include <functional>
#include <string>
#include <unordered_map>

namespace PasswordGuesstimator {

  enum class Err : uint64_t {
    ERR_FIRST = 0, // Must always be the first member of the enumeration

    ERR_NONE              = ERR_FIRST,
    ERR_UNIMPLEMENTED     = 0b1 << 0,
    ERR_NULLPTR           = 0b1 << 1,
    ERR_FAILS_RESTRICTONS = 0b1 << 2,

    ERR_LAST // Must always be the last member of the enumeration
  };
  inline const std::unordered_map<Err, std::string> ERR_STR_MAP{
    {Err::ERR_NONE, "ERR_NONE"},
    {Err::ERR_UNIMPLEMENTED, "ERR_UNIMPLEMENTED"},
    {Err::ERR_NULLPTR, "ERR_NULLPTR"},
    {Err::ERR_FAILS_RESTRICTONS, "ERR_FAILS_RESTRICTIONS"}
  };

  // Returns true if the provided function returns true
  // for all Err enumerations.
  auto for_err(std::function<bool(const Err)> const &f) -> bool;

  auto err_in_val(const Err err, const uint64_t val) -> bool;

  auto get_err_str(const uint64_t val) -> std::string;

} // namespace PasswordGuesstimator

#endif // GUESTIMATOR_ERR_H