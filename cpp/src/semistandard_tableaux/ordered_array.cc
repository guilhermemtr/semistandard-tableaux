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

    void
    ordered_array::copy (const ordered_array &o)
    {
      delete[] this->cells;

      this->size    = o.size;
      this->counter = o.counter;
      this->cells   = new entry[this->size];
      for (size_t i = 0; i < o.counter; i++)
      {
        this->cells[i] = o.cells[i];
      }
    }

    ordered_array::ordered_array (const ordered_array &o)
    {
      this->cells = new entry[0];
      this->copy (o);
    }

    ordered_array::~ordered_array ()
    {
      delete[] this->cells;
    }

    ordered_array &
    ordered_array::operator= (const ordered_array &o)
    {
      this->copy (o);
      return *this;
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

      if (this->counter > 0)
      {
        entry e (curr_val, count);
        this->cells[counter++] = e;
      }

      this->counter = counter;
    }

    bool
    ordered_array::operator== (const ordered_array &o) const
    {
      ordered_array o1 (*this);
      ordered_array o2 (o);

      o1.compress ();
      o2.compress ();

      if (o1.counter != o2.counter)
      {
        return false;
      }

      for (size_t i = 0; i < o1.counter; i++)
      {
        if (o1.cells[i] != o2.cells[i])
        {
          return false;
        }
      }
      return true;
    }

    bool
    ordered_array::operator!= (const ordered_array &o) const
    {
      return !(*this == o);
    }

    size_t
    ordered_array::get_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->counter; i++)
      {
        sz += this->cells[i].count;
      }
      return sz;
    }

    size_t
    ordered_array::get_mid (const entry_val val) const
    {
      size_t top    = this->counter - 1;
      size_t bottom = 0;
      size_t mid    = (top + bottom) >> 1;

      while (true)
      {
        if (val < this->cells[mid].val
            && (mid == 0 || val >= this->cells[mid - 1].val))
        {
          break;
        }

        if (val >= this->cells[mid].val)
        {
          bottom = mid + 1;
        } else
        {
          top = mid;
        }

        mid = (top + bottom) >> 1;
      }
      return mid;
    }

    void
    ordered_array::place_cell_mid (size_t *idx, const entry to_place)
    {
      if (*idx == 0 || this->cells[*idx - 1].val < to_place.val)
      {
        if (this->counter == this->size)
        {
          this->resize ();
        }

        for (size_t i = this->counter; i > *idx; i--)
        {
          this->cells[i] = this->cells[i - 1];
        }

        this->cells[*idx] = to_place;
        this->counter++;
        *idx = *idx + 1;
      } else    // this->cells[*idx - 1].val == to_place.val
      {
        this->cells[*idx - 1].count += to_place.count;
      }
    }

    void
    ordered_array::shift_cells_after_mid (size_t *  idx,
                                          entry_len extra,
                                          entry *   replaced,
                                          size_t *  pos)
    {
      size_t beg = 0;
      size_t dis = 0;

      while (extra > 0)
      {
        if (*idx >= this->counter)
        {
          extra = 0;
        } else if (extra >= this->cells[*idx].count)
        {
          if (dis == 0)
          {
            beg = *idx;
            dis = 1;
          } else
          {
            dis++;
          }
          replaced[*pos] = this->cells[*idx];
          *pos           = *pos + this->cells[*idx].count;
          extra          = extra - this->cells[*idx].count;
        } else    // extra < _sstoa[*idx].len
        {
          replaced[*pos]          = this->cells[*idx];
          replaced[*pos].count    = extra;
          this->cells[*idx].count = this->cells[*idx].count - extra;
          *pos                    = *pos + extra;
          extra                   = 0;
        }
        *idx = *idx + 1;
      }

      // shift all one to the left
      for (size_t i = beg; i + dis < this->counter; i++)
      {
        this->cells[i] = this->cells[i + dis];
      }
      this->counter -= dis;
    }

    void
    ordered_array::place_cell (entry to_place, entry *replaced, size_t *pos)
    {
      // if the cell is to be appended
      if (this->counter == 0
          || to_place.val >= this->cells[this->counter - 1].val)
      {
        if (this->counter == this->size)
        {
          this->resize ();
        }

        if ((this->counter == 0)
            || (to_place.val > this->cells[this->counter - 1].val))
        {
          this->cells[this->counter++] = to_place;
        } else    // this->cells[this->counter - 1].val == to_place.val
        {
          this->cells[this->counter - 1].count += to_place.count;
        }
        return;
      }

      // if the cell is not to be appended
      // search for correct position to place the cell
      size_t idx = this->get_mid (to_place.val);

      // place the cell
      this->place_cell_mid (&idx, to_place);

      // remove all the extra cells, starting at idx (to append them to another
      // row)
      this->shift_cells_after_mid (&idx, to_place.count, replaced, pos);
    }

    void
    ordered_array::add (entry * to_place,
                        size_t  real_nr_to_place,
                        entry * replaced,
                        size_t *real_nr_replaced)
    {
      size_t nr_placed  = 0;
      *real_nr_replaced = 0;

      // add the cells, one by one
      while (nr_placed < real_nr_to_place)
      {
        this->place_cell (to_place[nr_placed], replaced, real_nr_replaced);
        nr_placed += to_place[nr_placed].count;
      }
    }

    void
    ordered_array::write (FILE *f) const
    {
    }

    void
    ordered_array::resize ()
    {
      entry *cells = this->cells;
      this->size   = this->size * 2;
      this->cells  = new entry[this->size];

      for (size_t i = 0; i < this->counter; i++)
      {
        this->cells[i] = cells[i];
      }

      delete[] cells;
    }

  }    // namespace semistandard_tableaux

}    // namespace __placid


#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__
