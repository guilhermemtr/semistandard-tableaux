#include "tuple.hpp"

#ifdef __PLACID_TUPLE__

namespace __placid
{
  const std::string tuple_format_id = std::string ("tuple");
  
  const std::string incompatible_tuple_arities_exception =
    std::string ("Different tuple arities");

}    // namespace __placid

#endif    // __PLACID_TUPLE__
