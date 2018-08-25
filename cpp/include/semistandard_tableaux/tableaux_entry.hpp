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

      /** Creates an entry with length 0 and val 0.
       * Creates an entry with length 0 and val 0.
       */
      entry ();

      /** Creates an entry with length 1 and the given value.
       * Creates an entry with length 1 and the given value.
       * @param [in] val - the value.
       */
      entry (entry_val val);

      /** Creates an entry with the given length and the given value.
       * Creates an entry with the given length and the given value.
       * @param [in] val - the value.
       * @param [in] count - the length of the entry.
       */
      entry (entry_val val, entry_len count);

      /** Creates an entry from another entry.
       * Creates an entry from another entry.
       * @param [in] t - the entry from which the new entry will be created.
       */
      entry (const entry &t);

      /** Assigns the entry new values.
       * Assigns the entry new values.
       * @param [in] o - the values that the entry will take.
       * @return the entry.
       */
      entry &
      operator= (const entry &o);

      /** Assigns the entry a new value.
       * Assigns the entry a new value.
       * @param [in] val - the value that the entry will take.
       * @return the entry.
       */
      entry &
      operator= (const entry_val val);

      /** Checks if two entries are equal.
       * Checks if two entries are equal.
       * @param [in] e - the second entry.
       * @return if the two entries are equal.
       */
      bool
      operator== (const entry &e) const;

      /** Checks if two entries are different.
       * Checks if two entries are different.
       * @param [in] e - the second entry.
       * @return if the two entries are different.
       */
      bool
      operator!= (const entry &e) const;
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
