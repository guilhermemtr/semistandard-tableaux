#include "semistandard_tableaux.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX__

namespace __placid
{
  namespace semistandard_tableaux
  {
    tableaux::tableaux ()
    {
    }

    tableaux::tableaux (const tableaux &o)
    {
    }

    tableaux::~tableaux ()
    {
    }

    tableaux&
    tableaux::operator= (const tableaux& o)
    {
      return *this;
    }

    bool
    tableaux::operator== (const tableaux& o) const
    {
      return false;
    }

    tableaux tableaux::operator* (const tableaux& o) const
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
