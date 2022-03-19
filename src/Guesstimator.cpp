#include <Guesstimator.h>
#include <Guess.h>
#include <boost/multiprecision/cpp_int.hpp>

namespace PasswordGuesstimator {

  auto password_meets_restriction(std::string const &password, std::shared_ptr<const Restriction> p_restriction) -> uint64_t {
    if (!p_restriction) return static_cast<uint64_t>(Err::ERR_NULLPTR);
    if (!p_restriction->is_valid()) return static_cast<uint64_t>(Err::ERR_INVALID_RESTRICTION);
    if (password.length() < p_restriction->min_length()) return static_cast<uint64_t>(Err::ERR_FAILS_RESTRICTONS);
    if (!std::regex_match(password, p_restriction->character_set_regex())) return static_cast<uint64_t>(Err::ERR_FAILS_RESTRICTONS);
    return static_cast<uint64_t>(Err::ERR_NONE);
  }

  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<const Restriction> p_restriction) -> std::tuple<std::chrono::seconds, uint64_t> {
    auto err = static_cast<Err>(password_meets_restriction(password, p_restriction));
    if (err != static_cast<uint64_t>(Err::ERR_NONE)) {
      return {std::chrono::seconds(), static_cast<uint64_t>(err)};
    }

    using boost::multiprecision::cpp_int;
    using boost::multiprecision::pow;
    cpp_int total_possibilities = 0;
    for (auto i = p_restriction->min_length(); i <= password.length(); ++i) {
      total_possibilities += pow(cpp_int(p_restriction->character_set_size()), i);
    }

    // Losing precision here, but close enough.
    cpp_int duration_s = total_possibilities / GUESSES_PER_SECOND;
    return {std::chrono::seconds(duration_s.convert_to<uint64_t>()), static_cast<uint64_t>(err)};
  }

  auto brute_force(std::string const &answer, std::shared_ptr<const Restriction> p_restriction, std::ostream *os) -> std::tuple<std::chrono::seconds, uint64_t> {
    auto err = static_cast<Err>(password_meets_restriction(answer, p_restriction));
    if (err != static_cast<uint64_t>(Err::ERR_NONE)) {
      return {std::chrono::seconds(), static_cast<uint64_t>(err)};
    }

    auto start_t = std::chrono::steady_clock::now();
    for (Guess guess(p_restriction); guess != answer; ++guess) {
      if (os) *os << "PasswordGuesstimator::brute_force trying " << guess << "\n";
    }
    auto end_t = std::chrono::steady_clock::now();

    return {std::chrono::duration_cast<std::chrono::seconds>(end_t - start_t), static_cast<uint64_t>(Err::ERR_NONE)};
  }

} // namespace PasswordGuesstimator