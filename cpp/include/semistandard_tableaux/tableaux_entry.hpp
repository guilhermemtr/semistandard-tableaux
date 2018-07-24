#ifndef __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
#define __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

namespace __placid
{
  typedef uint64_t
    tableaux_entry_val;    //!< type of the value stored in tableaux cells.
  typedef uint64_t
    tableaux_entry_len;    //!< type of the length of tableaux cells.


  /** Type that represents a sequence of tableaux cells with the same value.
   * Type that represents a sequence of tableaux cells, with the same value, of
   * a certain length.
   */
  struct tableaux_cell
  {
    const std::string unmatching_values_exception =
      std::string ("Values of the entries do not match.");

    tableaux_entry_val val;      //!< value of the tableaux cell.
    tableaux_entry_len count;    //!< tableaux cell's sequence length.

    tableaux_cell (tableaux_entry_val val = 0L);

    tableaux_cell (tableaux_entry_val val, tableaux_entry_len count);

    tableaux_cell (tableaux_cell &t);

    bool
    equals (tableaux_cell o);

    tableaux_cell
    operator= (tableaux_cell o);

    tableaux_cell
    operator= (tableaux_entry_val val);

    tableaux_cell
    operator+= (tableaux_cell o);

    tableaux_cell
    operator-= (tableaux_cell o);

    tableaux_cell
    operator++ ();

    tableaux_cell
    operator++ (int v);

    tableaux_cell
    operator-- ();

    tableaux_cell
    operator-- (int v);

    tableaux_cell
    operator+ (tableaux_cell o);

    tableaux_cell
    operator- (tableaux_cell o);

    bool
    operator== (tableaux_cell o);

    bool
    operator!= (tableaux_cell o);

    bool
    operator< (tableaux_cell o);

    bool
    operator> (tableaux_cell o);

    bool
    operator<= (tableaux_cell o);

    bool
    operator>= (tableaux_cell o);
  };
}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
