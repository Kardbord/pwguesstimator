#ifndef GUESSTIMATOR_H
#define GUESSTIMATOR_H

#include <Err.h>
#include <Restriction.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace PasswordGuesstimator {

  const uint32_t MAX_THREADS = std::thread::hardware_concurrency();

  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction, std::ostream &stream = std::cout) -> Err;

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction, std::ostream &stream = std::cout) -> Err;

  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool;

} // namespace PasswordGuesstimator

#endif // GUESSTIMATOR_H