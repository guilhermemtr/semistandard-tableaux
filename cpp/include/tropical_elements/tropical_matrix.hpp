#ifndef __PLACID_TROPICAL_MATRIX__
#define __PLACID_TROPICAL_MATRIX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

#include "ring_element.hpp"
#include "tropical_number.hpp"

namespace __placid
{
  struct tropical_matrix : public ring_element<tropical_matrix>
  {
    size_t rows;
    size_t columns;
    tropical_number * matrix;

    /** Constructs a new tropical matrix, given its size (columns and rows).
     * Constructs a new tropical matrix, given its size (columns and rows).
     * @param columns the number of columns of the matrix.
     * @param rows the number of rows of the matrix.
     */
    tropical_matrix (size_t columns, size_t rows);

    /** Constructs a new tropical matrix, given its size (columns and rows), and the values of the matrix's entries.
     * Constructs a new tropical matrix, given its size (columns and rows), and the values of the matrix's entries.
     * The given values are cloned to the new matrix.
     * @param columns the number of columns of the matrix.
     * @param rows the number of rows of the matrix.
     * @param matrix the values of the entries of the matrix.
     */
    tropical_matrix (size_t columns, size_t rows, tropical_number *matrix);

    /** Destroys a tropical matrix.
     * Destroys a tropical matrix.
     */
    virtual ~tropical_matrix ();

    tropical_matrix
    operator= (tropical_matrix o);

    bool
    operator== (tropical_matrix o);

    tropical_matrix operator* (tropical_matrix o);

    tropical_matrix
    operator+ (tropical_matrix o);

    void
    read (FILE *f);

    void
    write (FILE *f);
  };

}    // namespace __placid

#endif    // __PLACID_TROPICAL_MATRIX__
