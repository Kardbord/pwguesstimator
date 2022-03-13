#include <Guesstimator.h>
#include <cstdlib>
#include <iostream>
#include <string>

auto main() -> int {
  const std::string password = "foobarbaz";
  auto p_restriction         = std::make_shared<PasswordGuesstimator::Alpha>(password.length());

  {
    auto[duration_s, err] = PasswordGuesstimator::guesstimate_brute_force_duration(password, p_restriction);
    if (err != PasswordGuesstimator::Err::ERR_NONE) {
      std::cerr << "Error during duration guesstimate! " << PasswordGuesstimator::get_err_str(err) << "\n";
    } else {
      std::cout << "It would take roughly " << duration_s.count() << " seconds to crack \"" << password << "\"\n";
    }
  }

  {
    auto[duration_s, err] = PasswordGuesstimator::brute_force(password, p_restriction);
    if (err != PasswordGuesstimator::Err::ERR_NONE) {
      std::cerr << "Error during brute force! " << PasswordGuesstimator::get_err_str(err) << "\n";
    } else {
      std::cout << "It took us " << duration_s.count() << " seconds to crack " << password << "\n";
    }
  }
  return EXIT_SUCCESS;
}