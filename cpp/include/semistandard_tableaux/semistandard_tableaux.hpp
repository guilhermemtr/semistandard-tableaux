#ifndef __PLACID_SEMISTANDARD_TABLEAUX__
#define __PLACID_SEMISTANDARD_TABLEAUX__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

#include "magma_element.hpp"

namespace __placid
{
  struct semistandard_tableaux : public magma_element<tropical_number>
  {
    static const file_format plain_format      = 0;
    static const file_format compressed_format = 1;
    static const file_format table_format      = 2;

    /** Constructs a new semistandard tableaux.
     * Constructs a new semistandard tableaux.
     */
    semistandard_tableaux ();

    /** Constructs a new semistandard tableaux, given .
     * Constructs a new tropical number, given its value.
     * @param n the number of the tropical number to be created.
     */
    semistandard_tableaux (tn_t n);

    /** Destroys a tropical number structure.
     * Destroys a tropical number structure.
     */
    virtual ~semistandard_tableaux ();

    semistandard_tableaux
    operator= (semistandard_tableaux o);

    bool
    operator== (semistandard_tableaux o);

    semistandard_tableaux operator* (semistandard_tableaux o);

    void
    read (FILE *f);

    void
    write (FILE *f, file_format format);
  };

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
