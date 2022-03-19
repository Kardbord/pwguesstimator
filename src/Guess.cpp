#include <Guess.h>
#include <iterator>

namespace PasswordGuesstimator {
  Guess::Guess(std::shared_ptr<const Restriction> p_restriction): mp_restriction(p_restriction), m_guess() {
    if (!mp_restriction)
      throw std::invalid_argument("Cannot construct internal class PasswordGuesstimator::Guess from nullptr. This is an internal bug and should be reported.");
    m_guess = std::string(mp_restriction->min_length(), *(mp_restriction->character_set().cbegin()));
  }

  auto Guess::operator==(std::string const &other) const -> bool {
    return this->m_guess == other;
  }

  auto Guess::operator!=(std::string const &other) const -> bool {
    return !(*this == other);
  }

  auto operator<<(std::ostream &os, Guess const &guess) -> std::ostream & {
    os << guess.m_guess;
    return os;
  }

  auto Guess::operator++() -> Guess & {
    static auto cs_itr             = mp_restriction->character_set().cbegin();

    ++cs_itr;
    if (cs_itr == mp_restriction->character_set().cend()) {
      rollover(m_guess.length() - 1);
      cs_itr = mp_restriction->character_set().cbegin();
      return *this;
    }
    m_guess[m_guess.length() - 1] = *cs_itr;
    return *this;
  }

  auto Guess::rollover(int32_t const idx) ->void {
    // Roll over the index
    m_guess[idx] = *mp_restriction->character_set().cbegin();

    // Increment the next significant index
    if (idx - 1 < 0) {
      // All out of characters, have to generate a new guess and start over.
      m_guess = std::string(m_guess.length()+1, *mp_restriction->character_set().cbegin());
      return;
    }
    auto next_it = std::next(mp_restriction->character_set().find(m_guess[idx - 1]));
    if (next_it == mp_restriction->character_set().cend()) {
      // We need to roll over the next character as well.
      rollover(idx - 1);
      return;
    }
    m_guess[idx - 1] = *next_it;
  }

} // namespace PasswordGuesstimator