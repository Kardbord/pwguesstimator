#ifndef GUESSTIMATOR_ERR_H
#define GUESSTIMATOR_ERR_H

#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>

namespace PasswordGuesstimator {

  enum class Err : uint64_t {
    ERR_FIRST = 0, // Must always be the first member of the enumeration

    ERR_NONE                = ERR_FIRST,
    ERR_UNIMPLEMENTED       = 0b1 << 0,
    ERR_NULLPTR             = 0b1 << 1,
    ERR_FAILS_RESTRICTONS   = 0b1 << 2,
    ERR_INVALID_RESTRICTION = 0b1 << 3,

    ERR_LAST // Must always be the last member of the enumeration
  };
  inline const std::unordered_map<Err, std::string> ERR_STR_MAP{
    {Err::ERR_NONE, "ERR_NONE"},
    {Err::ERR_UNIMPLEMENTED, "ERR_UNIMPLEMENTED"},
    {Err::ERR_NULLPTR, "ERR_NULLPTR"},
    {Err::ERR_FAILS_RESTRICTONS, "ERR_FAILS_RESTRICTIONS"},
    {Err::ERR_INVALID_RESTRICTION, "ERR_INVALID_RESTRICTION"},
  };

  // Returns true if the provided function returns true
  // for all Err enumerations.
  auto for_err(std::function<bool(const Err)> const &f) -> bool;

  auto err_in_val(const Err err, const uint64_t val) -> bool;

  auto get_err_str(const uint64_t val) -> std::string;

  auto operator==(Err a, uint64_t b) -> uint64_t;
  auto operator!=(Err a, uint64_t b) -> uint64_t;
  auto operator<(Err a, uint64_t b)  -> uint64_t;
  auto operator>(Err a, uint64_t b)  -> uint64_t;
  auto operator<=(Err a, uint64_t b) -> uint64_t;
  auto operator>=(Err a, uint64_t b) -> uint64_t;
  auto operator==(uint64_t a, Err b) -> uint64_t;
  auto operator!=(uint64_t a, Err b) -> uint64_t;
  auto operator<(uint64_t a, Err b)  -> uint64_t;
  auto operator>(uint64_t a, Err b)  -> uint64_t;
  auto operator<=(uint64_t a, Err b) -> uint64_t;
  auto operator>=(uint64_t a, Err b) -> uint64_t;

  auto operator|(Err a, Err b) -> uint64_t;

  auto operator&(Err a, uint64_t b)  -> uint64_t;
  auto operator|(Err a, uint64_t b)  -> uint64_t;
  auto operator^(Err a, uint64_t b)  -> uint64_t;
  auto operator<<(Err a, uint64_t b) -> uint64_t;
  auto operator>>(Err a, uint64_t b) -> uint64_t;

  auto operator&(Err a, uint32_t b)  -> uint64_t;
  auto operator|(Err a, uint32_t b)  -> uint64_t;
  auto operator^(Err a, uint32_t b)  -> uint64_t;
  auto operator<<(Err a, uint32_t b) -> uint64_t;
  auto operator>>(Err a, uint32_t b) -> uint64_t;

  auto operator<<(std::ostream& os, const Err &err) -> std::ostream&;

} // namespace PasswordGuesstimator

#endif // GUESSTIMATOR_ERR_H