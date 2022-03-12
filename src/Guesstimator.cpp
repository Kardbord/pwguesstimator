#include <Guesstimator.h>

namespace PasswordGuesstimator {

  auto password_meets_restriction(std::string const &password, std::shared_ptr<Restriction> const &p_restriction) -> bool {
    if (!p_restriction) return false;
    return std::regex_match(password, p_restriction->character_set_regex());
  }

  auto guesstimate_brute_force_duration(std::string const &password, std::shared_ptr<Restriction> const &p_restriction, std::ostream &stream) -> Err {
    (void) stream;
    if (!p_restriction) return Err::ERR_NULLPTR;
    if (!password_meets_restriction(password, p_restriction)) return Err::ERR_FAILS_RESTRICTONS;
    return Err::ERR_UNIMPLEMENTED;
  }

  auto brute_force(std::string const &answer, std::shared_ptr<Restriction> const &p_restriction, std::ostream &stream) -> Err {
    (void) stream;
    if (!p_restriction) return Err::ERR_NULLPTR;
    if (!password_meets_restriction(answer, p_restriction)) return Err::ERR_FAILS_RESTRICTONS;
    return Err::ERR_UNIMPLEMENTED;
  }

} // namespace PasswordGuesstimator