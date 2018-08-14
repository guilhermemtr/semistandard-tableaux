#ifndef __PLACID_TROPICAL_MATRIX__
#define __PLACID_TROPICAL_MATRIX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>
#include <cctype>

#include "ring_element.hpp"
#include "tropical_number.hpp"

namespace __placid
{
  namespace tropical_elements
  {
    extern const std::string tropical_matrix_format_id;
    extern const std::string invalid_matrix_sizes_exception;

    struct matrix : public ring_element<matrix>
    {
      static const file_format plain_format = 0;
      static const file_format table_format = 1;

      size_t  rows;
      size_t  columns;
      number *matrix_entries;

      /** Constructs a new tropical matrix, given its size (columns and rows).
       * Constructs a new tropical matrix, given its size (columns and rows).
       * @param rows the number of rows of the matrix.
       * @param columns the number of columns of the matrix.
       */
      matrix (size_t rows = 0, size_t columns = 0);

      /** Constructs a new tropical matrix, given its size (columns and rows),
       * and the values of the matrix's entries. Constructs a new tropical
       * matrix, given its size (columns and rows), and the values of the
       * matrix's entries. The given values are cloned to the new matrix.
       * @param rows the number of rows of the matrix.
       * @param columns the number of columns of the matrix.
       * @param matrix the values of the entries of the matrix.
       */
      matrix (size_t rows, size_t columns, number *matrix_entries);

      /** Constructs a new tropical matrix, from another tropical matrix.
       * Constructs a new tropical matrix, from another tropical matrix.
       * The given values are cloned to the new matrix.
       * @param o the tropical matrix to be cloned.
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
      void
      read_plain (FILE *f);

      void
      read_table (FILE *f);

      void
      write_plain (FILE *f) const;

      void
      write_table (FILE *f) const;
    };

  }    // namespace tropical_elements

}    // namespace __placid

#endif    // __PLACID_TROPICAL_MATRIX__
