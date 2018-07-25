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

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__
