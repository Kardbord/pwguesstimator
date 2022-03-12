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

  // Returns a PasswordGuesstimator Err(s) in the form of a uint64.
  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction, std::ostream &stream = std::cout) -> uint64_t;

  // Returns a PasswordGuesstimator Err(s) in the form of a uint64.
  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction, std::ostream &stream = std::cout) -> uint64_t;

  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool;

} // namespace PasswordGuesstimator

#endif // GUESSTIMATOR_H