#ifndef RESTRICTION_H
#define RESTRICTION_H

#include <regex>
#include <set>

namespace PasswordGuesstimator {

  class Restriction {
  public:
    virtual auto character_set() const -> const std::set<char>   & = 0;
    virtual auto character_set_regex() const -> const std::regex & = 0;
    virtual auto min_length() const -> uint32_t                    = 0;

    auto character_set_size() const -> uint64_t {
      return character_set().size();
    };

    auto is_valid() const -> bool {
      if (character_set_size() == 0) return false;
      if (min_length() == 0) return false;
      return true;
    }
  };

  class PrintableAscii: public Restriction {
  public:
    PrintableAscii() = delete;
    PrintableAscii(const uint32_t min_length): m_min_length(min_length) {
    }

    // ASCII codes 32 to 126 are printable
    static inline const std::set<char> CHARACTER_SET = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',  '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', ':', ';', '<', '=', '>', '?',  '@', 'A', 'B', 'C', 'D',  'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',  'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',  'p', 'q', 'r', 's', 't',  'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~',
    };
    static inline const std::regex PRINTABLE_ASCII_REGEX = std::regex("[ -~]+");

    inline auto character_set() const -> const std::set<char> & override {
      return CHARACTER_SET;
    }
    inline auto character_set_regex() const -> const std::regex & override {
      return PRINTABLE_ASCII_REGEX;
    }
    inline auto min_length() const -> uint32_t override {
      return m_min_length;
    }

  private:
    const uint32_t m_min_length;
  };

  class Alpha: public Restriction {
  public:
    Alpha() = delete;
    Alpha(const uint32_t min_length): m_min_length(min_length) {
    }

    static inline const std::set<char> CHARACTER_SET = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    };
    static inline const std::regex ALPHA_REGEX = std::regex("[a-zA-Z]+");

    inline auto character_set() const -> const std::set<char> & override {
      return CHARACTER_SET;
    }
    inline auto character_set_regex() const -> const std::regex & override {
      return ALPHA_REGEX;
    }
    inline auto min_length() const -> uint32_t override {
      return m_min_length;
    }

  private:
    const uint32_t m_min_length;
  };

  class Numeric: public Restriction {
  public:
    Numeric() = delete;
    Numeric(const uint32_t min_length): m_min_length(min_length) {
    }

    static inline const std::set<char> CHARACTER_SET = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    };
    static inline const std::regex NUMERIC_REGEX = std::regex("[0-9]+");

    inline auto character_set() const -> const std::set<char> & override {
      return CHARACTER_SET;
    }
    inline auto character_set_regex() const -> const std::regex & override {
      return NUMERIC_REGEX;
    }
    inline auto min_length() const -> uint32_t override {
      return m_min_length;
    }

  private:
    const uint32_t m_min_length;
  };

  class AlphaNumeric: public Restriction {
  public:
    AlphaNumeric() = delete;
    AlphaNumeric(const uint32_t min_length): m_min_length(min_length) {
    }

    static inline const std::set<char> CHARACTER_SET = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
        'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    };
    static inline const std::regex ALPHANUMERIC_REGEX = std::regex("[a-zA-Z0-9]+");

    inline auto character_set() const -> const std::set<char> & override {
      return CHARACTER_SET;
    }
    inline auto character_set_regex() const -> const std::regex & override {
      return ALPHANUMERIC_REGEX;
    }
    inline auto min_length() const -> uint32_t override {
      return m_min_length;
    }

  private:
    const uint32_t m_min_length;
  };

} // namespace PasswordGuesstimator

#endif