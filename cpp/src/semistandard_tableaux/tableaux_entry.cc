#include "tableaux_entry.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

namespace __placid
{
  tableaux_cell::tableaux_cell (uint32_t val, uint32_t count)
    : val (val), count (count)
  {
  }

  tableaux_cell::tableaux_cell (uint32_t val) : tableaux_cell (val, 1)
  {
  }

  tableaux_cell::tableaux_cell (tableaux_cell &t)
    : tableaux_cell (t.val, t.count)
  {
  }

  tableaux_cell
  tableaux_cell::operator= (tableaux_cell o)
  {
    this->val   = o.val;
    this->count = o.count;
    return *this;
  }
}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
