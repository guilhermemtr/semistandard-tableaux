#ifndef __PLACID_FREE_MONOID_ELEMENT__
#define __PLACID_FREE_MONOID_ELEMENT__

#include <string>

#include "magma_element.hpp"
#include "free_monoid_entry.hpp"

namespace __placid
{
  namespace free_monoid
  {
    extern const std::string free_monoid_format_id;

    struct free_monoid_element : public magma_element<free_monoid_element>
    {
      static const size_t      default_size      = 0;
      static const file_format plain_format      = 0;
      static const file_format compressed_format = 1;

      size_t length;
      entry *word;

      /** Constructs a new free monoid element.
       * Constructs a new free monoid element.
       */
      free_monoid_element (size_t size = default_size);

      free_monoid_element (symbol *w, size_t len);

      /** Constructs a new free monoid element, from a given free monoid
       * element. Constructs a new free monoid element, from a given free monoid
       * element.
       * @param o the free monoid element.
       */
      free_monoid_element (free_monoid_element &o);

      /** Destroys a free monoid.
       * Destroys a free monoid.
       */
      ~free_monoid_element ();

      free_monoid_element
      operator= (free_monoid_element o);

      bool
      operator== (free_monoid_element o);

      bool
      operator!= (free_monoid_element o);

      free_monoid_element operator* (free_monoid_element o);

      void
      add (symbol *s, size_t count);

      size_t
      get_size ();

      void
      compress ();

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format);

        private:
      void
      read_plain (FILE *f, size_t lines);

      void
      read_compressed (FILE *f, size_t lines);

      void
      write_plain (FILE *f);

      void
      write_compressed (FILE *f);
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_ELEMENT__
