#ifndef __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
#define __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

namespace __placid
{
  /** Type that represents a sequence of tableaux cells with the same value.
   * Type that represents a sequence of tableaux cells, with the same value, of
   * a certain length.
   */
  struct tableaux_cell
  {
    uint32_t val;      //!< value of the tableaux cell.
    uint32_t count;    //!< tableaux cell's sequence length.

    tableaux_cell (uint32_t val, uint32_t count);

    tableaux_cell (uint32_t val);

    tableaux_cell (tableaux_cell &t);

    tableaux_cell
    operator= (tableaux_cell o);
  };
}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRy__
