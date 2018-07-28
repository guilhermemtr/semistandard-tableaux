#include "semistandard_tableaux.hpp"
#ifdef __PLACID_SEMISTANDARD_TABLEAUX__

namespace __placid
{
  namespace semistandard_tableaux
  {
    tableaux::tableaux (size_t size)
    {
      this->size    = size;
      this->counter = 0;
      this->rows    = new ordered_array[this->size];
    }

    tableaux::tableaux (const tableaux &o) : tableaux (o.size)
    {
      this->counter = o.counter;

      for (size_t i = 0; i < this->counter; i++)
      {
        this->rows[i] = o.rows[i];
      }
    }

    tableaux::tableaux (const free_monoid::element &o) : tableaux ()
    {
      // TODO
    }

    tableaux::~tableaux ()
    {
      delete[] this->rows;
    }

    tableaux &
    tableaux::operator= (const tableaux &o)
    {
      if (this->size != o.size)
      {
        delete[] this->rows;
        this->size    = o.size;
        this->counter = o.counter;
      }

      for (size_t i = 0; i < this->counter; i++)
      {
        this->rows[i] = o.rows[i];
      }

      return *this;
    }

    bool
    tableaux::operator== (const tableaux &o) const
    {
      if (this->counter != o.counter)
      {
        return false;
      }

      for (size_t i = 0; i < this->counter; i++)
      {
        if (this->rows[i] != o.rows[i])
        {
          return false;
        }
      }

      return true;
    }

    size_t
    tableaux::get_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->counter; i++)
      {
        sz += this->rows[i].get_size ();
      }
      return sz;
    }

    size_t
    tableaux::get_storage_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->counter; i++)
      {
        sz += this->rows[i].counter;
      }
      return sz;
    }

    free_monoid::element
    tableaux::get_reading () const
    {
      return free_monoid::element ();
    }

    tableaux tableaux::operator* (const tableaux &o) const
    {
      return o;
    }

    void
    tableaux::read (FILE *f)
    {
      return;
    }

    void
    tableaux::write (FILE *f, file_format format) const
    {
      return;
    }


    void
    tableaux::read_plain (FILE *f)
    {
    }

    void
    tableaux::read_compressed (FILE *f)
    {
    }

    void
    tableaux::read_table (FILE *f) const
    {
    }

    void
    tableaux::write_plain (FILE *f) const
    {
    }

    void
    tableaux::write_compressed (FILE *f) const
    {
    }

    void
    tableaux::write_table (FILE *f)
    {
    }

    size_t
    tableaux::add_cells (const free_monoid::element &word)
    {
      size_t word_len = word.get_size ();

      entry arr1[word_len];
      entry arr2[word_len];

      entry *to_place = arr1;
      entry *replaced = arr2;

      size_t result_sz = 0;



      for (size_t i = 0, j = 0; j < word_len; j += word.word[i++].count)
      {
        entry e (word.word[i].sym, word.word[i].count);
        to_place[j] = e;
      }

      size_t j = 0;

      while (word_len != 0)
      {
        if (j == this->counter)
        {
          if (this->counter == this->size)
          {
            this->resize ();
          }
          this->counter++;
        }

        this->rows[j].add (to_place, word_len, replaced, &word_len);

        result_sz += this->rows[j++].counter;

        entry *tmp = to_place;
        to_place   = replaced;
        replaced   = tmp;
      }
      return result_sz;
    }

    void
    tableaux::resize ()
    {
      ordered_array *old = this->rows;
      this->size         = this->size * 2;
      this->rows         = new ordered_array[this->size];

      for (size_t i = 0; i < this->counter; i++)
      {
        this->rows[i] = old[i];
      }

      delete[] old;
    }

    void
    tableaux::iterate (iteration_function fn, void *data)
    {
      size_t index      = 0;
      size_t real_index = 0;
      size_t i          = 0;
      size_t j          = this->counter;
      while (j != 0)
      {
        while (i < this->rows[j - 1].counter)
        {
          fn (this->rows[j - 1].cells[i], index++, real_index, data);
          real_index += this->rows[j - 1].cells[i++].count;
        }
        i = 0;
        j--;
      }
    }



  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
