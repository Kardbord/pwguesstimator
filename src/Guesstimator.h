#ifndef GUESSTIMATOR_H
#define GUESSTIMATOR_H

#include <Restriction.h>
#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace PasswordGuesstimator {

  const uint32_t MAX_THREADS = std::thread::hardware_concurrency();

  class GuesstimatorResult {
  public:
    enum class Err {
      ERR_NONE,
      ERR_UNIMPLEMENTED,
    };

    GuesstimatorResult() = delete;
    GuesstimatorResult(const Err err, const std::chrono::milliseconds duration);

    auto get_duration() -> const std::chrono::milliseconds & {
      return m_duration;
    }
    auto get_err() -> const Err & {
      return m_err;
    }

  private:
    Err                       m_err;
    std::chrono::milliseconds m_duration;
  };

  auto guesstimate_brute_force_duration(std::string const &answer, std::shared_ptr<Restriction> const &restriction) -> GuesstimatorResult;

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &restriction) -> GuesstimatorResult;

}; // namespace PasswordGuesstimator

#endif // GUESSTIMATOR_H