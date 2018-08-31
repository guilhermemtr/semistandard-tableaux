#include "tropical_number.hpp"

#ifdef __PLACID_TROPICAL_NUMBER__

namespace __placid
{
  namespace tropical_elements
  {
    const std::string tn_str_format   = std::string ("%lu");
    const std::string tn_str_infinite = std::string ("-");
    const tn_t        tn_infinite     = (1L << 32L);

    number::number ()
    {
      this->n = tn_infinite;
    }

    number::number (const tn_t &n)
    {
      this->n = n;
    }

    number::number (const number &o)
    {
      this->n = o.n;
    }

    number::~number ()
    {
    }

    bool
    number::finite () const
    {
      return !(this->n >> (sizeof (tn_t) * 8 / 2));
    }

    tn_t
    number::get () const
    {
      return this->n;
    }

    number &
    number::operator= (const tn_t &o)
    {
      this->n = o;
      return *this;
    }

    number &
    number::operator= (const number &o)
    {
      this->n = o.n;
      return *this;
    }

    bool
    number::operator== (const number &o) const
    {
      return !(this->finite () || o.finite ()) || (this->n == o.n);
    }

    number number::operator* (const number &o) const
    {
      return number (this->n + o.n);
    }

    number
    number::operator+ (const number &o) const
    {
      tn_t res;
      if (this->finite () && o.finite ())
      {
        res = this->n > o.n ? this->n : o.n;
      } else
      {
        res = this->n > o.n ? o.n : this->n;
      }

      const tn_t r = res;
      return number (r);
    }

    void
    number::read (FILE *f)
    {
      char val[256];
      if (fscanf (f, "%256s", val) != 1)
      {
        throw invalid_file_format_exception;
      }

      tn_t v;

      if (strcmp (tn_str_infinite.c_str (), val) == 0)
      {
        v = number ().get ();
      } else
      {
        v = atoll (val);
      }

      this->n = v;
    }

    void
    number::write (FILE *f, file_format format) const
    {
      if (f == NULL)
      {
        return;
      }

      if (format != plain_format)
      {
        throw invalid_file_format_exception;
      }

      if (this->finite ())
      {
        fprintf (f, (tn_str_format + " ").c_str (), this->get ());
      } else
      {
        fprintf (f, (tn_str_infinite + " ").c_str ());
      }
    }

  }    // namespace tropical_elements

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
