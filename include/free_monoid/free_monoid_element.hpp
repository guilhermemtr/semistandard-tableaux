#ifndef __PLACID_FREE_MONOID_ELEMENT__
#define __PLACID_FREE_MONOID_ELEMENT__

#include <string>

#include "free_monoid_entry.hpp"

#include "magma_element.hpp"


namespace __placid
{
  namespace free_monoid
  {
    extern const std::string
      free_monoid_format_id;    // !< the id of the format of a free monoid
                                // element.

    /**
     * This class defines a word element.
     * This class defines a word element.
     * A word element is an element from a mathematical structure called the
     * free monoid.
     * Although a word should be a subtype of a factor monoid element, doing so
     * would cause a circular dependency, and so, instead of making the word
     * element a subtype of a factor_monoid_element, we implement all the
     * methods of the factor_monoid_element to allow to use this as a
     * factor_monoid_element would be used.
     */
    struct element : public magma_element<element>
    {
      static const size_t default_size = 0;    // !< the default size of a word.

      static const file_format plain_format = 0;    // !< the plain format id.
      static const file_format compressed_format =
        1;    // !< the compressed format id.

      size_t length;    // !< the length of the word.
      entry *word;      // !< the contents of the word.

      /** Constructs a new free monoid element, with the given size.
       * Constructs a new free monoid element, with the given size.
       * @param [in] size - the size of the word.
       */
      element (size_t size = default_size);

      /** Constructs a new free monoid element given a vector of symbols.
       * Constructs a new free monoid element given a vector of symbols.
       * @param [in] w - the vector of symbols.
       * @param [in] len - the length of the vector of symbols.
       */
      element (symbol *w, size_t len);

      /** Constructs a new free monoid element, from a given free monoid
       * element. Constructs a new free monoid element, from a given free monoid
       * element.
       * @param [in] o - the free monoid element.
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

      /** Adds a vector of symbols to the word.
       * Adds a vector of symbols to the word.
       * @param [in] s - the vector of symbols.
       * @param [in] count - the length of the vector of symbols.
       */
      void
      add (symbol *s, size_t count);

      /** Adds a vector of entries to the word.
       * Adds a vector of entries to the word.
       * @param [in] entries - the vector of entries.
       * @param [in] length - the length of the vector of entries.
       */
      void
      add (entry *entries, size_t length);

      /** Gets the size of the word.
       * Gets the size of the word.
       * @return the size of the word.
       */
      size_t
      get_size () const;

      /** Compresses the word.
       * Compresses the word.
       */
      void
      compress ();

      element
      reading () const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format) const;

      // private:
      /** Reads a word in the plain format from the given file
       * stream. Reads a word in the plain format from the given file
       * stream.
       * @param [in] f - the file stream.
       * @param [in] lines - the number of lines.
       */
      void
      read_plain (FILE *f, size_t lines);

      /** Reads a word in the compressed format from the given file
       * stream. Reads a word in the compressed format from the given file
       * stream.
       * @param [in] f - the file stream.
       * @param [in] lines - the number of lines.
       */
      void
      read_compressed (FILE *f, size_t lines);

      /** Writes the word in plain format to the given file stream.
       * Writes the word in plain format to the given file stream.
       * @param [in] f - the file stream.
       */
      void
      write_plain (FILE *f) const;

      /** Writes the word in table format to the given file stream.
       * Writes the word in table format to the given file stream.
       * @param [in] f - the file stream.
       */
      void
      write_compressed (FILE *f) const;
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_ELEMENT__
