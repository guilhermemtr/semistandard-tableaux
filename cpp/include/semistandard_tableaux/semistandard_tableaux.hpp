#ifndef __PLACID_SEMISTANDARD_TABLEAUX__
#define __PLACID_SEMISTANDARD_TABLEAUX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

#include "magma_element.hpp"

namespace __placid
{
  namespace semistandard_tableaux
  {
    struct tableaux : public magma_element<tableaux>
    {
      static const file_format plain_format      = 0;
      static const file_format compressed_format = 1;
      static const file_format table_format      = 2;

      /** Constructs a new semistandard tableaux.
       * Constructs a new semistandard tableaux.
       */
      tableaux ();

      /** Constructs a new semistandard tableaux, given .
       * Constructs a new tropical number, given its value.
       * @param o the semistandard tableaux.
       */
      tableaux (tableaux &o);

      /** Destroys a tropical number structure.
       * Destroys a tropical number structure.
       */
      virtual ~tableaux ();

      tableaux
      operator= (tableaux o);

      bool
      operator== (tableaux o);

      tableaux operator* (tableaux o);

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format);
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
