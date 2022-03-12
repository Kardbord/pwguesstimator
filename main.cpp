#include <Guesstimator.h>
#include <cstdlib>
#include <iostream>
#include <string>

auto main() -> int {
  const std::string password = "foobarbaz";
  auto p_restriction         = std::make_shared<PasswordGuesstimator::Alpha>();
  std::cout << std::boolalpha << "Password meets restrictions: " << PasswordGuesstimator::password_meets_restriction(password, p_restriction) << "\n";
  return EXIT_SUCCESS;
}