#ifndef GUESSTIMATOR_H
#define GUESSTIMATOR_H

#include <Err.h>
#include <Restriction.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <tuple>

namespace PasswordGuesstimator {

  // Rough estimate based on numbers from Hashcat (https://hashcat.net/).
  // A Hashcat official twitter post claims a cracking speed of 100GH/s
  // for NTLM-hashed passwords using hashcat 6.0.0 on a single NVIDIA
  // 2080Ti GPU. (https://twitter.com/hashcat/status/1095807014079512579)
  //
  // Note that the brute_force function included in this library will be
  // significantly slower than hashcat. This number is used for guesstimating
  // how quickly a password could be brute-forced in the real world.
  constexpr uint64_t GUESSES_PER_SECOND = 100'000'000'000;

  // Guesstimates how long it might take to crack a given password based on GUESSES_PER_SECOND.
  //
  // Returns a tuple
  // {Guesstimation of how long it will take to brute force the password in seconds, PasswordGuesstimator Err(s) in the form of a uint64}
  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> std::tuple<std::chrono::seconds, uint64_t>;

  // Max threads that will be used by this library's brute_force function.
  const uint32_t MAX_THREADS = std::thread::hardware_concurrency();

  // Takes a very naive approach to brute-forcing a given password.
  //
  // Returns a tuple
  // {Duration of brute force in milliseconds, PasswordGuesstimator Err(s) in the form of a uint64}
  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction) -> std::tuple<std::chrono::seconds, uint64_t>;

  // Checks if a provided password meets a provided Restriction set.
  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool;

} // namespace PasswordGuesstimator

#endif // GUESSTIMATOR_H