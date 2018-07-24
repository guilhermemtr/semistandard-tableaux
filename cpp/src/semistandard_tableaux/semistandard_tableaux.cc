#include "semistandard_tableaux.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX__

namespace __placid
{
  semistandard_tableaux::semistandard_tableaux ()
  {
  }

  semistandard_tableaux::semistandard_tableaux (semistandard_tableaux& o)
  {
  }

  semistandard_tableaux::~semistandard_tableaux ()
  {
  }

  semistandard_tableaux
  semistandard_tableaux::operator= (semistandard_tableaux o)
  {
    return o;
  }

  bool
  semistandard_tableaux::operator== (semistandard_tableaux o)
  {
    return false;
  }

  semistandard_tableaux semistandard_tableaux::
                        operator* (semistandard_tableaux o)
  {
    return o;
  }

  void
  semistandard_tableaux::read (FILE *f)
  {
    return;
  }

  void
  semistandard_tableaux::write (FILE *f, file_format format)
  {
    return;
  }

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
