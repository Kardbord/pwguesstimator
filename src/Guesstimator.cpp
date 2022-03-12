#include <Guesstimator.h>

namespace PasswordGuesstimator {

  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool {
    if (!p_restriction) return false;
    return std::regex_match(password, p_restriction->character_set_regex());
  }

  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> std::tuple<std::chrono::milliseconds, uint64_t> {
    if (!p_restriction) return {std::chrono::milliseconds(), static_cast<uint64_t>(Err::ERR_NULLPTR)};

    uint64_t err = static_cast<uint64_t>(Err::ERR_NONE);
    if (!password_meets_restriction(password, p_restriction)) return {std::chrono::milliseconds(), static_cast<uint64_t>(Err::ERR_FAILS_RESTRICTONS)};
    return {std::chrono::milliseconds(), Err::ERR_UNIMPLEMENTED | err};
  }

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction) -> std::tuple<std::chrono::milliseconds, uint64_t> {
    if (!p_restriction) return {std::chrono::milliseconds(), static_cast<uint64_t>(Err::ERR_NULLPTR)};

    uint64_t err = static_cast<uint64_t>(Err::ERR_NONE);
    if (!password_meets_restriction(answer, p_restriction)) return {std::chrono::milliseconds(), static_cast<uint64_t>(Err::ERR_FAILS_RESTRICTONS)};
    return {std::chrono::milliseconds(), Err::ERR_UNIMPLEMENTED | err};
  }

} // namespace PasswordGuesstimator