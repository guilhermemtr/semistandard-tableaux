#ifndef __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
#define __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

namespace __placid
{
  namespace semistandard_tableaux
  {
    typedef uint64_t
                     entry_val;    //!< type of the value stored in tableaux cells.
    typedef uint64_t entry_len;    //!< type of the length of tableaux cells.


    /** Type that represents a sequence of tableaux cells with the same value.
     * Type that represents a sequence of tableaux cells, with the same value,
     * of a certain length.
     */
    struct entry
    {
      entry_val val;      //!< value of the tableaux cell.
      entry_len count;    //!< tableaux cell's sequence length.

      entry ();

      entry (entry_val val);

      entry (entry_val val, entry_len count);

      entry (const entry &t);

      entry &
      operator= (const entry &o);

      entry &
      operator= (const entry_val val);

      bool
      operator== (const entry &e) const;

      bool
      operator!= (const entry &e) const;
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
