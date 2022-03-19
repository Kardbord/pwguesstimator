#include <Guesstimator.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>

auto clear_cin() -> void {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Prompt for a restriction set and password to try and crack.
auto prompt() -> std::tuple<std::shared_ptr<PasswordGuesstimator::Restriction>, std::string> {
  using PasswordGuesstimator::Alpha;
  using PasswordGuesstimator::AlphaNumeric;
  using PasswordGuesstimator::Err;
  using PasswordGuesstimator::Numeric;
  using PasswordGuesstimator::password_meets_restriction;
  using PasswordGuesstimator::PrintableAscii;
  using PasswordGuesstimator::Restriction;

  class InputOpt {
  public:
    InputOpt() = delete;
    InputOpt(std::string const name, std::function<std::shared_ptr<Restriction>(uint32_t const)> factory): m_name(name), m_factory(factory) {}

    auto name() const -> std::string { return m_name; }
    auto build(uint32_t const min_len) const -> std::shared_ptr<Restriction> { return m_factory(min_len); }

  private:
    std::string m_name;
    std::function<std::shared_ptr<Restriction>(uint32_t const)> m_factory;
  };

  static const std::map<uint16_t, InputOpt> restriction_menu{
      {1, {"PrintableAscii", [](uint32_t const min_len) -> std::shared_ptr<Restriction> { return std::make_shared<PrintableAscii>(min_len); }}},
      {2, {"Alpha", [](uint32_t const min_len) -> std::shared_ptr<Restriction> { return std::make_shared<Alpha>(min_len); }}},
      {3, {"Numeric", [](uint32_t const min_len) -> std::shared_ptr<Restriction> { return std::make_shared<Numeric>(min_len); }}},
      {4, {"AlphaNumeric", [](uint32_t const min_len) -> std::shared_ptr<Restriction> { return std::make_shared<AlphaNumeric>(min_len); }}},
  };

  std::cout << "\nSelect your ruleset.\n";
  for (auto const &[key, opt]: restriction_menu) {
    std::cout << "  " << key << " - " << opt.name() << "\n";
  }
  std::cout << "Input the number of your selection: ";

  uint32_t ruleset_selection = 0;
  while (!(std::cin >> ruleset_selection) || restriction_menu.count(ruleset_selection) == 0) {
    std::cout << "Invalid selection, try again: ";
    clear_cin();
  }

  std::cout << "Input the minimum password length restriction [1, inf]: ";
  uint32_t min_length = 0;
  while (!(std::cin >> min_length) || min_length < 1) {
    std::cout << "Invalid selection, try again: ";
    clear_cin();
  }

  auto p_restriction = restriction_menu.at(ruleset_selection).build(min_length);
  std::string pw     = "";
  std::cout << "Input a password for the Guesstimator to crack.\n";
  std::cout << "Requirements: \n";
  std::cout << "  Minimum Length: " << p_restriction->min_length() << "\n";
  std::cout << "  Regex Pattern: " << p_restriction->character_set_regex_str() << "\n";
  std::cout << "Input your selection: ";
  while (!(std::cin >> pw) || password_meets_restriction(pw, p_restriction) != Err::ERR_NONE) {
    std::cout << "Provided password does not meet requirements of selected ruleset, try again: ";
    clear_cin();
  }

  return {p_restriction, pw};
}

auto main() -> int {
  for (;;) {
    std::cout << "\x1B[2J\x1B[HWelcome to PasswordGuesstimator.\n";
    std::cout << "Press CTRL+c at any time to exit.\n";

    auto [p_restriction, password] = prompt();
    {
      auto [duration_s, err] = PasswordGuesstimator::guesstimate_brute_force_duration(password, p_restriction);
      if (err != PasswordGuesstimator::Err::ERR_NONE) {
        std::cerr << "Error during duration guesstimate! " << PasswordGuesstimator::get_err_str(err) << "\n";
      } else {
        std::cout << "It would take roughly " << duration_s.count() << " seconds for an optimal setup to crack \"" << password << "\"\n";
      }
    }

    static std::string yn = "n";
    static std::unordered_set<std::string> yes_inputs{"y", "Y", "yes", "Yes", "YES"};
    std::cout << "Would you like the PasswordGuesstimator to try and crack your password? It may take quite awhile. [y/N]: ";
    if (!(std::cin >> yn) || yes_inputs.count(yn) == 0) {
      clear_cin();
      std::cout << "\nWould you like to go again? [y/N]: ";
      if (!(std::cin >> yn) || yes_inputs.count(yn) == 0) break;
      continue;
    }
    std::cout << "\nAttempting to crack your password, this may take awhile... " << std::flush;
    {
      auto [duration_s, err] = PasswordGuesstimator::brute_force(password, p_restriction);
      if (err != PasswordGuesstimator::Err::ERR_NONE) {
        std::cerr << "Error during brute force! " << PasswordGuesstimator::get_err_str(err) << "\n";
      } else {
        std::cout << "It took us " << duration_s.count() << " seconds to crack " << password << "\n";
      }
    }

    std::cout << "\nWould you like to go again? [y/N]: ";
    if (!(std::cin >> yn) || yes_inputs.count(yn) == 0) break;
  }
  std::cout << "Goodbye.\n";
  return EXIT_SUCCESS;
}