#include "ordered_array.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

namespace __placid
{
  tableaux_ordered_array::tableaux_ordered_array (size_t size)
    : size (size), counter (0)
  {
    this->cells = new tableaux_cell[this->size];
  }

  tableaux_ordered_array::tableaux_ordered_array (tableaux_ordered_array &o)
    : tableaux_ordered_array (o.size)
  {
    for (size_t i = 0; i < o.counter; i++)
    {
      this->cells[i] = o.cells[i];
    }
  }

  tableaux_ordered_array::~tableaux_ordered_array ()
  {
    delete[] this->cells;
  }

  tableaux_ordered_array
  tableaux_ordered_array::operator= (tableaux_ordered_array o)
  {
    delete[] this->cells;

    this->size    = o.size;
    this->counter = o.counter;
    this->cells   = new tableaux_cell[this->size];
    for (size_t i = 0; i < o.counter; i++)
    {
      this->cells[i] = o.cells[i];
    }
    return o;
  }

  size_t
  tableaux_ordered_array::get_size ()
  {
    size_t sz = 0;
    for (size_t i = 0; i < this->counter; i++)
    {
      sz += this->cells[i].count;
    }
    return sz;
  }

  /*  void
  tableaux_ordered_array::add (tableaux_cell *to_place,
                               size_t         real_nr_to_place,
                               tableaux_cell *replaced,
                               size_t *       real_nr_replaced)
  {
  }*/
}    // namespace __placid


#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__
