#ifndef __PLACID_SEMISTANDARD_TABLEAUX__
#define __PLACID_SEMISTANDARD_TABLEAUX__

#include <string>
#include <functional>

#include <cstdint>
#include <cassert>
#include <cstring>

#include "ordered_array.hpp"

#include "free_monoid/factor_monoid_element.hpp"




namespace __placid
{
  namespace semistandard_tableaux
  {
    extern const std::string
      semistandard_tableaux_format_id;    // !< the format id of the
                                          // semistandard tableaux.

    /**
     * This class defines a semistandard tableaux.
     * This class defines a semistandard tableaux.
     */
    struct tableaux : public free_monoid::factor_element<tableaux>
    {
      static const size_t default_size =
        (1 << 5);    // !< the default size of the semistandard tableaux.

      static const file_format plain_format =
        0;    // !< id representing the plain format.
      static const file_format compressed_format =
        1;    // !< id representing the compressed format.
      static const file_format table_format =
        2;    // !< id representing the table format.

      size_t size;       // !< the size of the semistandard tableaux.
      size_t counter;    // !< the current size of the semistandard tableaux.
      ordered_array *rows;    // !< the rows of the semistandard tableaux.

      /** Constructs a new semistandard tableaux with the given size.
       * Constructs a new semistandard tableaux with the given size.
       * @param [in] size - the size of the semistandard tableaux to be created.
       */
      tableaux (size_t size = default_size);

      /** Constructs a new semistandard tableaux, given another semistandard
       * tableaux. Constructs a new semistandard tableaux, given another
       * semistandard tableaux.
       * @param [in] o - the semistandard tableaux.
       */
      tableaux (const tableaux &o);

      /** Constructs a new semistandard tableaux, given a word.
       * Constructs a new semistandard tableaux, given a word.
       * @param [in] o - the word.
       */
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

      /** Gets the size of the semistandard tableaux.
       * Gets the size of the semistandard tableaux.
       * @return the size of the semistandard tableaux.
       */
      size_t
      get_size () const;

      /** Gets the real size of the semistandard tableaux.
       * Gets the real size of the semistandard tableaux.
       * @return the real size of the semistandard tableaux.
       */
      size_t
      get_storage_size () const;

      free_monoid::element
      reading () const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format) const;

      /** Appends a word to the semistandard tableaux.
       * Appends a word to the semistandard tableaux.
       * @param [in] word - the word to be appended.
       */
      void
      append (const free_monoid::element &word);

        private:
      /** Iterates the semistandard tableaux, applying the given function at
       * each step of the iteration. Iterates the semistandard tableaux,
       * applying the given function at each step of the iteration.
       * @param [in] fn - the function to be applied.
       * @param [in] data - the data to be passed to the function.
       */
      void
      iterate (const std::function<void(entry, size_t, size_t, void *)> &fn,
               void *data) const;
      /** Resizes the semistandard tableaux.
       * Resizes the semistandard tableaux.
       */
      void
      resize ();

      /** Reads a semistandard tableaux in the table format from the given file
       * stream. Reads a semistandard tableaux in the table format from the
       * given file stream.
       * @param [in] f - the file stream.
       * @param [in] lines - the number of lines.
       */
      void
      read_table (FILE *f, size_t lines);

      /** Writes the semistandard tableaux in table format to the given file
       * stream. Writes the semistandard tableaux in table format to the given
       * file stream.
       * @param [in] f - the file stream.
       */
      void
      write_table (FILE *f) const;
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
