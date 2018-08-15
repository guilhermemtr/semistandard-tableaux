#ifndef __PLACID_FREE_MONOID_ELEMENT__
#define __PLACID_FREE_MONOID_ELEMENT__

#include <string>

#include "magma_element.hpp"
#include "free_monoid_entry.hpp"
#include "factor_monoid_element.hpp"

namespace __placid
{
  namespace semistandard_tableaux
  {
    struct tableaux;
  }

  namespace free_monoid
  {
    extern const std::string free_monoid_format_id;
    
    struct element : public factor_element<element>
    {
      friend semistandard_tableaux::tableaux;

      static const size_t default_size = 0;

      static const file_format plain_format      = 0;
      static const file_format compressed_format = 1;

      size_t length;
      entry *word;

      /** Constructs a new free monoid element.
       * Constructs a new free monoid element.
       */
      element (size_t size = default_size);

      element (symbol *w, size_t len);

      /** Constructs a new free monoid element, from a given free monoid
       * element. Constructs a new free monoid element, from a given free monoid
       * element.
       * @param o the free monoid element.
       */
      element (const element &o);

      /** Destroys a free monoid.
       * Destroys a free monoid.
       */
      ~element ();

      element &
      operator= (const element &o);

      bool
      operator== (const element &o) const;

      element operator* (const element &o) const;

      void
      add (symbol *s, size_t count);

      void
      add (entry *entries, size_t length);

      size_t
      get_size () const;

      void
      compress ();

      element
      reading () const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format) const;

        private:
      void
      read_plain (FILE *f, size_t lines);

      void
      read_compressed (FILE *f, size_t lines);

      void
      write_plain (FILE *f) const;

      void
      write_compressed (FILE *f) const;
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_ELEMENT__
