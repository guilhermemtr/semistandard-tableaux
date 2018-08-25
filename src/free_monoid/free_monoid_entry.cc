#include "free_monoid_entry.hpp"

#ifdef __PLACID_FREE_MONOID_ENTRY__

namespace __placid
{
  namespace free_monoid
  {
    entry::entry (symbol sym, occurrences count) : sym (sym), count (count)
    {
    }

    entry::entry (symbol sym) : entry (sym, 1)
    {
    }

    entry::entry (entry &t) : entry (t.sym, t.count)
    {
    }

    entry
    entry::operator= (entry o)
    {
      this->sym   = o.sym;
      this->count = o.count;
      return *this;
    }

    entry
    entry::operator= (symbol sym)
    {
      this->sym   = sym;
      this->count = 1;

      return *this;
    }

    bool
    entry::operator== (entry o)
    {
      return this->sym == o.sym && this->count == o.count;
    }

    bool
    entry::operator!= (entry o)
    {
      return !(*this == o);
    }

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_ENTRY__
