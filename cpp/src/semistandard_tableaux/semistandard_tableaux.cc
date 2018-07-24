#include "semistandard_tableaux.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX__

namespace __placid
{
  namespace semistandard_tableaux
  {
    tableaux::tableaux ()
    {
    }

    tableaux::tableaux (tableaux &o)
    {
    }

    tableaux::~tableaux ()
    {
    }

    tableaux
    tableaux::operator= (tableaux o)
    {
      return o;
    }

    bool
    tableaux::operator== (tableaux o)
    {
      return false;
    }

    tableaux tableaux::operator* (tableaux o)
    {
      return o;
    }

    void
    tableaux::read (FILE *f)
    {
      return;
    }

    void
    tableaux::write (FILE *f, file_format format)
    {
      return;
    }

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
