#ifndef __PLACID_FREE_MONOID_ENTRY__
#define __PLACID_FREE_MONOID_ENTRY__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

namespace __placid
{
  namespace free_monoid
  {
    typedef uint64_t symbol;    // !< represents the type of a symbol of a
                                // semistandard tableaux.
    typedef uint64_t
      occurrences;    // !< represents the type used to define the number of
                      // occurrences of a symbol in the tableaux.

    /**
     * This class defines an entry of a semistandard tableaux.
     * This class defines an entry of a semistandard tableaux.
     */
    struct entry
    {
      symbol      sym; // !< the symbol of the entry.
      occurrences count; // !< the number of occurrences of the symbol.

      /** Creates a new entry given a value.
       * Creates a new entry given a value.
       * @param [in] sym - the symbol.
       */
      entry (symbol sym = 0L);

      /** Creates a new entry given a value and the number of occurrences.
       * Creates a new entry given a value and the number of occurrences.
       * @param [in] sym - the symbol.
       * @param [in] count - the number of occurrences.
       */
      entry (symbol sym, occurrences count);

      /** Creates a new entry given another entry.
       * Creates a new entry given another entry.
       * @param [in] t - the other entry.
       */
      entry (entry &t);

      /** Assigns a new entry to the entry.
       * Assigns a new entry to the entry.
       * @param [in] o - the new entry.
       * @return a reference to the value of the entry.
       */
      entry
      operator= (entry o);

      /** Assigns a new value to the entry, with count set to 1.
       * Assigns a new value to the entry, with count set to 1.
       * @param [in] sym - the new symbol of the entry.
       * @return a reference to the value of the entry.
       */
      entry
      operator= (symbol sym);

      /** Checks if two entries are equal.
       * Checks if two entries are equal.
       * @param [in] o - the second entry.
       * @return if the two entries are equal.
       */
      bool
      operator== (entry e);

      /** Checks if two entries are different.
       * Checks if two entries are different.
       * @param [in] o - the second entry.
       * @return if the two entries are different.
       */
      bool
      operator!= (entry e);
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
