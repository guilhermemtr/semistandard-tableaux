#include "tableaux_entry.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__

namespace __placid
{
  tableaux_cell::tableaux_cell (tableaux_entry_val val,
                                tableaux_entry_len count)
    : val (val), count (count)
  {
  }

  tableaux_cell::tableaux_cell (tableaux_entry_val val) : tableaux_cell (val, 1)
  {
  }

  tableaux_cell::tableaux_cell (tableaux_cell &t)
    : tableaux_cell (t.val, t.count)
  {
  }

  bool
  tableaux_cell::equals (tableaux_cell o)
  {
    return this->val == o.val && this->count == o.count;
  }

  tableaux_cell
  tableaux_cell::operator= (tableaux_cell o)
  {
    this->val   = o.val;
    this->count = o.count;
    return *this;
  }

  tableaux_cell
  tableaux_cell::operator= (tableaux_entry_val val)
  {
    this->val   = val;
    this->count = 1;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator+= (tableaux_cell o)
  {
    if (this->val != o.val)
    {
      throw unmatching_values_exception;
    }

    this->count += o.count;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator-= (tableaux_cell o)
  {
    if (this->val != o.val)
    {
      throw unmatching_values_exception;
    }

    this->count -= o.count;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator++ ()
  {
    this->count++;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator++ (int v)
  {
    this->count++;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator-- ()
  {
    this->count--;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator-- (int v)
  {
    this->count--;

    return *this;
  }

  tableaux_cell
  tableaux_cell::operator+ (tableaux_cell o)
  {
    if (this->val != o.val)
    {
      throw unmatching_values_exception;
    }

    tableaux_cell res (this->val, this->count + o.count);

    return res;
  }

  tableaux_cell
  tableaux_cell::operator- (tableaux_cell o)
  {
    if (this->val != o.val)
    {
      throw unmatching_values_exception;
    }

    tableaux_cell res (this->val, this->count - o.count);

    return res;
  }

  bool
  tableaux_cell::operator== (tableaux_cell o)
  {
    return this->val == o.val;
  }

  bool
  tableaux_cell::operator!= (tableaux_cell o)
  {
    return !(*this == o);
  }

  bool
  tableaux_cell::operator< (tableaux_cell o)
  {
    return this->val < o.val;
  }

  bool
  tableaux_cell::operator> (tableaux_cell o)
  {
    return this->val > o.val;
  }

  bool
  tableaux_cell::operator<= (tableaux_cell o)
  {
    return this->val <= o.val;
  }

  bool
  tableaux_cell::operator>= (tableaux_cell o)
  {
    return this->val >= o.val;
  }

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ENTRY__
