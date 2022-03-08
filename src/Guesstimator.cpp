#include <Guesstimator.h>

namespace PasswordGuesstimator {

  GuesstimatorResult::GuesstimatorResult(const Err err, const std::chrono::milliseconds duration): m_err(err), m_duration(duration) {
  }

  auto guesstimate_brute_force_duration(std::string const &answer, std::shared_ptr<Restriction> const &restriction) -> GuesstimatorResult {
    return GuesstimatorResult {GuesstimatorResult::Err::ERR_UNIMPLEMENTED, std::chrono::milliseconds(0)};
  }

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &restriction) -> GuesstimatorResult {
    return GuesstimatorResult {GuesstimatorResult::Err::ERR_UNIMPLEMENTED, std::chrono::milliseconds(0)};
  }

} // namespace PasswordGuesstimator