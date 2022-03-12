#include <Guesstimator.h>
#include <cstdlib>
#include <iostream>
#include <string>

auto main() -> int {
  const std::string password = "foobarbaz";
  auto p_restriction         = std::make_shared<PasswordGuesstimator::Alpha>();

  PasswordGuesstimator::Err err = PasswordGuesstimator::Err::ERR_NONE;
  std::cout << "Err is " << PasswordGuesstimator::get_err_str(static_cast<uint64_t>(err)) << "\n";
  err = PasswordGuesstimator::guesstimate_brute_force_duration(password, p_restriction);
  std::cout << "Err is " << PasswordGuesstimator::get_err_str(static_cast<uint64_t>(err)) << "\n";
  err = PasswordGuesstimator::brute_force(password, p_restriction);
  std::cout << "Err is " << PasswordGuesstimator::get_err_str(static_cast<uint64_t>(err)) << "\n";
  return EXIT_SUCCESS;
}