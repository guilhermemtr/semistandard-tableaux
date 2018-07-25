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
    typedef uint64_t symbol;
    typedef uint64_t occurrences;

    struct entry
    {
      symbol      sym;
      occurrences count;

      entry (symbol sym = 0L);

      entry (symbol sym, occurrences count);

      entry (entry &t);

      entry
      operator= (entry o);

      entry
      operator= (symbol sym);

      bool
      operator== (entry e);

      bool
      operator!= (entry e);
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
