#ifndef __PLACID_SEMISTANDARD_TABLEAUX__
#define __PLACID_SEMISTANDARD_TABLEAUX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

#include <functional>

#include "free_monoid/free_monoid_element.hpp"
#include "ordered_array.hpp"

#include "magma_element.hpp"

namespace __placid
{
  namespace semistandard_tableaux
  {
    extern const std::string semistandard_tableaux_format_id;

    struct tableaux : public magma_element<tableaux>
    {
      static const size_t default_size = (1 << 5);

      static const file_format plain_format      = 0;
      static const file_format compressed_format = 1;
      static const file_format table_format      = 2;

      size_t         size;
      size_t         counter;
      ordered_array *rows;

      /** Constructs a new semistandard tableaux.
       * Constructs a new semistandard tableaux.
       */
      tableaux (size_t size = default_size);

      /** Constructs a new semistandard tableaux, given .
       * Constructs a new tropical number, given its value.
       * @param o the semistandard tableaux.
       */
      tableaux (const tableaux &o);

      tableaux (const free_monoid::element &o);

      /** Destroys a tropical number structure.
       * Destroys a tropical number structure.
       */
      virtual ~tableaux ();

      tableaux &
      operator= (const tableaux &o);

      tableaux &
      operator= (const free_monoid::element &o);

      bool
      operator== (const tableaux &o) const;

      size_t
      get_size () const;

      size_t
      get_storage_size () const;

      free_monoid::element
      get_reading () const;

      tableaux operator* (const tableaux &o) const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format) const;

        private:
      void
      iterate (const std::function<void(entry, size_t, size_t, void *)> &fn,
               void *data) const;

      void
      add_cells (const free_monoid::element &word);

      void
      resize ();

      void
      read_table (FILE *f, size_t lines);

      void
      write_table (FILE *f) const;
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
