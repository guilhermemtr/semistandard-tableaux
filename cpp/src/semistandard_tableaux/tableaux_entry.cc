#include "tableaux_entry.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__

namespace __placid
{
  namespace semistandard_tableaux
  {
    entry::entry (entry_val val, entry_len count) : val (val), count (count)
    {
    }

    entry::entry (entry_val val) : entry (val, 1)
    {
    }

    entry::entry () : entry (0, 0)
    {
    }

    entry::entry (const entry &t) : entry (t.val, t.count)
    {
    }

    entry &
    entry::operator= (const entry &o)
    {
      this->val   = o.val;
      this->count = o.count;
      return *this;
    }

    entry &
    entry::operator= (const entry_val val)
    {
      this->val   = val;
      this->count = 1;

      return *this;
    }

    bool
    entry::operator== (const entry &o) const
    {
      return this->val == o.val && this->count == o.count;
    }

    bool
    entry::operator!= (const entry &o) const
    {
      return !(*this == o);
    }

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
