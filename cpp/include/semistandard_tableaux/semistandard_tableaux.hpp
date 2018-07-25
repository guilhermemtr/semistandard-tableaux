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
      tableaux (const tableaux &o);

      // tableaux (free_monoid &o);

      /** Destroys a tropical number structure.
       * Destroys a tropical number structure.
       */
      virtual ~tableaux ();

      tableaux&
      operator= (const tableaux& o);

      bool
      operator== (const tableaux& o) const;

      size_t
      get_size () const;

      size_t
      get_storage_size () const;

      // free_monoid
      // get_reading();

      tableaux operator* (const tableaux& o) const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format) const;

        private:
      void
      read_plain (FILE *f);

      void
      read_compressed (FILE *f);

      void
      read_table (FILE *f) const;

      void
      write_plain (FILE *f) const;

      void
      write_compressed (FILE *f) const;

      void
      write_table (FILE *f);
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
