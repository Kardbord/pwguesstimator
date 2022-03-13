#include <Guesstimator.h>
#include <boost/multiprecision/cpp_int.hpp>

namespace PasswordGuesstimator {

  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool {
    if (!p_restriction) return false;
    if (password.length() < p_restriction->min_length()) return false;
    return std::regex_match(password, p_restriction->character_set_regex());
  }

  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> std::tuple<std::chrono::seconds, uint64_t> {
    using boost::multiprecision::cpp_int;
    if (!p_restriction) return {std::chrono::seconds(), static_cast<uint64_t>(Err::ERR_NULLPTR)};
    if (!password_meets_restriction(password, p_restriction)) return {std::chrono::seconds(), static_cast<uint64_t>(Err::ERR_FAILS_RESTRICTONS)};

    using boost::multiprecision::pow;
    cpp_int total_possibilities = 0;
    for (auto i = p_restriction->min_length(); i <= password.length(); ++i) {
      total_possibilities += pow(cpp_int(p_restriction->character_set_size()), i);
    }

    // Losing precision here, but close enough.
    cpp_int duration_s = total_possibilities / GUESSES_PER_SECOND;
    return {std::chrono::seconds(duration_s.convert_to<uint64_t>()), static_cast<uint64_t>(Err::ERR_NONE)};
  }

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction) -> std::tuple<std::chrono::seconds, uint64_t> {
    if (!p_restriction) return {std::chrono::seconds(), static_cast<uint64_t>(Err::ERR_NULLPTR)};
    if (!password_meets_restriction(answer, p_restriction)) return {std::chrono::seconds(), static_cast<uint64_t>(Err::ERR_FAILS_RESTRICTONS)};

    uint64_t err = static_cast<uint64_t>(Err::ERR_NONE);
    return {std::chrono::seconds(), Err::ERR_UNIMPLEMENTED | err};
  }

} // namespace PasswordGuesstimator