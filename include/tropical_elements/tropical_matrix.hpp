#ifndef __PLACID_TROPICAL_MATRIX__
#define __PLACID_TROPICAL_MATRIX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>
#include <cctype>

#include "tropical_number.hpp"

namespace __placid
{
  namespace tropical_elements
  {
    extern const std::string
      tropical_matrix_format_id;    // !< represents the format id of tropical
                                    // matrices.
    extern const std::string
      invalid_matrix_sizes_exception;    // !< corresponds to an exception that
                                         // is thrown when an operation between
                                         // matrices with incompatible sizes is
                                         // issued.

    /**
     * This class defines a tropical matrix.
     * This class defines a tropical matrix.
     */
    struct matrix : public ring_element<matrix>
    {
      static const file_format plain_format =
        0;    // !< represents the format corresponding to the plain format of a
              // tropical matrix.
      static const file_format table_format =
        1;    // !< represents the format corresponding to the table format of a
              // tropical matrix.

      size_t  rows;       // !< the number of rows of the tropical matrix.
      size_t  columns;    // !< the number of columns of the tropical matrix.
      number *matrix_entries;    // !< the entries of the tropical matrix.

      /** Constructs a new tropical matrix, given its size (columns and rows).
       * Constructs a new tropical matrix, given its size (columns and rows).
       * @param [in] rows - the number of rows of the matrix.
       * @param [in] columns - the number of columns of the matrix.
       */
      matrix (size_t rows = 0, size_t columns = 0);

      /** Constructs a new tropical matrix, given its size (columns and rows),
       * and the values of the matrix's entries. Constructs a new tropical
       * matrix, given its size (columns and rows), and the values of the
       * matrix's entries. The given values are cloned to the new matrix.
       * @param [in] rows - the number of rows of the matrix.
       * @param [in] columns - the number of columns of the matrix.
       * @param [in] matrix - the values of the entries of the matrix.
       */
      matrix (size_t rows, size_t columns, number *matrix_entries);

      /** Constructs a new tropical matrix, from another tropical matrix.
       * Constructs a new tropical matrix, from another tropical matrix.
       * The given values are cloned to the new matrix.
       * @param [in] o - the tropical matrix to be cloned.
       */
      matrix (const matrix &o);

      /** Destroys a tropical matrix.
       * Destroys a tropical matrix.
       */
      virtual ~matrix ();

      matrix &
      operator= (const matrix &o);

      bool
      operator== (const matrix &o) const;

      matrix operator* (const matrix &o) const;

      matrix
      operator+ (const matrix &o) const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format) const;

        private:
      /** Reads a tropical matrix in the plain format from the given file
       * stream. Reads a tropical matrix in the plain format from the given file
       * stream.
       * @param [in] f - the file stream.
       */
      void
      read_plain (FILE *f);

      /** Reads a tropical matrix in the table format from the given file
       * stream. Reads a tropical matrix in the table format from the given file
       * stream.
       * @param [in] f - the file stream.
       */
      void
      read_table (FILE *f);

      /** Writes the tropical matrix in plain format to the given file stream.
       * Writes the tropical matrix in plain format to the given file stream.
       * @param [in] f - the file stream.
       */
      void
      write_plain (FILE *f) const;

      /** Writes the tropical matrix in table format to the given file stream.
       * Writes the tropical matrix in table format to the given file stream.
       * @param [in] f - the file stream.
       */
      void
      write_table (FILE *f) const;
    };

  }    // namespace tropical_elements

}    // namespace __placid

#endif    // __PLACID_TROPICAL_MATRIX__
