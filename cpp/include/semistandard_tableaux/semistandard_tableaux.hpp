#ifndef __PLACID_SEMISTANDARD_TABLEAUX__
#define __PLACID_SEMISTANDARD_TABLEAUX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

#include "free_monoid/free_monoid_element.hpp"

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

      // tableaux (free_monoid &o);

      /** Destroys a tropical number structure.
       * Destroys a tropical number structure.
       */
      virtual ~tableaux ();

      tableaux
      operator= (tableaux o);

      bool
      operator== (tableaux o);

      size_t
      get_size ();

      size_t
      get_storage_size ();

      // free_monoid
      // get_reading();

      tableaux operator* (tableaux o);

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format);

        private:
      void
      read_plain (FILE *f);

      void
      read_compressed (FILE *f);

      void
      read_table (FILE *f);

      void
      write_plain (FILE *f);

      void
      write_compressed (FILE *f);

      void
      write_table (FILE *f);
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
