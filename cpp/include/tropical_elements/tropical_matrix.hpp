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

    /** Constructs a new tropical number, given its value.
     * Constructs a new tropical number, given its value.
     * @param n the number of the tropical number to be created.
     */
    tropical_matrix (size_t columns, size_t rows);

    /** Destroys a tropical number structure.
     * Destroys a tropical number structure.
     */
    virtual ~tropical_matrix ();

    tropical_matrix
    operator= (tropical_matrix &o);

    bool
    operator== (tropical_matrix &o);

    bool
    operator!= (tropical_matrix &o);

    tropical_matrix operator* (tropical_matrix &o);

    tropical_matrix
    operator+ (tropical_matrix &o);

    void
    read (FILE *f);

    void
    read (std::string fn);

    void
    write (FILE *f);

    void
    write (std::string fn);
  };

}    // namespace __placid

#endif    // __PLACID_TROPICAL_MATRIX__
