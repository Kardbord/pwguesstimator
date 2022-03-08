#ifndef RESTRICTION_H
#define RESTRICTION_H

#include <regex>

namespace PasswordGuesstimator {

  class Restriction {
  public:
    virtual auto character_set_size() -> uint64_t            = 0;
    virtual auto character_set_regex() -> const std::regex & = 0;
  };

  class PrintableAscii: public Restriction {
  public:
    static inline const std::regex   PRINTABLE_ASCII_REGEX = std::regex("[ -~]+");
    static inline constexpr uint64_t CHARACTER_SET_SIZE    = 95; // Codes 32 to 126 are printable

    inline auto character_set_size() -> uint64_t override {
      return CHARACTER_SET_SIZE;
    }
    inline auto character_set_regex() -> const std::regex & override {
      return PRINTABLE_ASCII_REGEX;
    }
  };

  class Alpha: public Restriction {
  public:
    static inline const std::regex   ALPHA_REGEX        = std::regex("[a-zA-Z]");
    static inline constexpr uint64_t CHARACTER_SET_SIZE = 52;

    inline auto character_set_size() -> uint64_t override {
      return CHARACTER_SET_SIZE;
    }
    inline auto character_set_regex() -> const std::regex & override {
      return ALPHA_REGEX;
    }
  };

  class Numeric: public Restriction {
  public:
    static inline const std::regex   NUMERIC_REGEX      = std::regex("[0-9]+");
    static inline constexpr uint64_t CHARACTER_SET_SIZE = 10;

    inline auto character_set_size() -> uint64_t override {
      return CHARACTER_SET_SIZE;
    }

    inline auto character_set_regex() -> const std::regex & override {
      return NUMERIC_REGEX;
    }
  };

  class AlphaNumeric: public Restriction {
  public:
    static inline const std::regex   ALPHANUMERIC_REGEX = std::regex("[a-zA-Z0-9]");
    static inline constexpr uint64_t CHARACTER_SET_SIZE = 62;

    inline auto character_set_size() -> uint64_t override {
      return CHARACTER_SET_SIZE;
    }

    inline auto character_set_regex() -> const std::regex & override {
      return ALPHANUMERIC_REGEX;
    }
  };

} // namespace PasswordGuesstimator

#endif