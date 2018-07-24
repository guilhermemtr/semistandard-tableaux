#include "ordered_array.hpp"

#ifdef __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

namespace __placid
{
  namespace semistandard_tableaux
  {
    ordered_array::ordered_array (size_t size) : size (size), counter (0)
    {
      this->cells = new entry[this->size];
    }

    ordered_array::ordered_array (ordered_array &o) : ordered_array (o.size)
    {
      for (size_t i = 0; i < o.counter; i++)
      {
        this->cells[i] = o.cells[i];
      }
    }

    ordered_array::~ordered_array ()
    {
      delete[] this->cells;
    }

    ordered_array
    ordered_array::operator= (ordered_array o)
    {
      delete[] this->cells;

      this->size    = o.size;
      this->counter = o.counter;
      this->cells   = new entry[this->size];
      for (size_t i = 0; i < o.counter; i++)
      {
        this->cells[i] = o.cells[i];
      }
      return o;
    }

    void
    ordered_array::compress ()
    {
      entry_val curr_val =
        this->counter > 0 ? this->cells[0].val : 0;    // current value read
      entry_len count   = 0;    // number of repetitions of current value
      size_t    counter = 0;    // current compressed counter
      for (size_t i = 0; i < this->counter; i++)
      {
        if (this->cells[i].val == curr_val)
        {
          count += this->cells[i].count;
        } else
        {
          entry cell (curr_val, count);
          this->cells[counter++] = cell;
          curr_val               = this->cells[i].val;
          count                  = this->cells[i].count;
        }
      }
      this->counter = counter;
    }

    bool
    ordered_array::operator== (ordered_array o)
    {
      this->compress ();
      o.compress ();

      if (this->counter != o.counter)
      {
        return false;
      }

      for (size_t i = 0; i < this->counter; i++)
      {
        if (this->cells[i] != o.cells[i])
        {
          return false;
        }
      }
      return true;
    }

    bool
    ordered_array::operator!= (ordered_array o)
    {
      return !(*this == o);
    }

    size_t
    ordered_array::get_size ()
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->counter; i++)
      {
        sz += this->cells[i].count;
      }
      return sz;
    }

    /*  void
    ordered_array::add (entry *to_place,
                                 size_t         real_nr_to_place,
                                 entry *replaced,
                                 size_t *       real_nr_replaced)
    {
    }*/

    void
    ordered_array::write (FILE *f)
    {
    }

    void
    ordered_array::resize ()
    {
    }

  }    // namespace semistandard_tableaux

}    // namespace __placid


#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__
