#ifndef PASSWORD_GUESSTIMATOR_GUESS
#define PASSWORD_GUESSTIMATOR_GUESS

#include <Restriction.h>
#include <iostream>
#include <memory>

namespace PasswordGuesstimator {
  class Guess {
  public:
    Guess(std::shared_ptr<const Restriction> p_restriction);

    // Increment to the next guess.
    //
    // Generates guesses similarly to how one would count upward.
    // For example, if we were generating guesses for a numeric
    // 4 digit password, we would make the following guesses:
    // 0000
    // 0001
    // ....
    // 0009
    // 0010
    // 0011
    // ....
    // 9999
    // The same principle can be applied to non-numeric guesses.
    // It's just easier for me to reason about it this way. :)
    auto operator++() -> Guess &;

    auto operator==(std::string const &other) const -> bool;
    auto operator!=(std::string const &other) const -> bool;

    friend auto operator<<(std::ostream &os, Guess const &guess) -> std::ostream &;

  private:
    // Rolls over the given guess index and any subsequent indices.
    auto rollover(int32_t const idx) -> void;

    std::shared_ptr<const Restriction> mp_restriction{nullptr};
    std::string m_guess{};
  };
} // namespace PasswordGuesstimator

#endif
