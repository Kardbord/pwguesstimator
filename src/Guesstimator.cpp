#include <Guesstimator.h>

namespace PasswordGuesstimator {

  GuesstimatorResult::GuesstimatorResult(const Err err, const std::chrono::milliseconds duration): m_err(err), m_duration(duration) {
  }

  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool {
    if (!p_restriction) return false;
    return std::regex_match(password, p_restriction->character_set_regex());
  }

  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> GuesstimatorResult {
    (void) password;
    if (!p_restriction) return GuesstimatorResult{GuesstimatorResult::Err::ERR_NULLPTR, std::chrono::milliseconds(0)};
    return GuesstimatorResult{GuesstimatorResult::Err::ERR_UNIMPLEMENTED, std::chrono::milliseconds(0)};
  }

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction) -> GuesstimatorResult {
    (void) answer;
    if (!p_restriction) return GuesstimatorResult{GuesstimatorResult::Err::ERR_NULLPTR, std::chrono::milliseconds(0)};
    return GuesstimatorResult{GuesstimatorResult::Err::ERR_UNIMPLEMENTED, std::chrono::milliseconds(0)};
  }

} // namespace PasswordGuesstimator