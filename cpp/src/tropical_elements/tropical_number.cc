#include "tropical_number.hpp"

#ifdef __PLACID_TROPICAL_NUMBER__

namespace __placid
{
  namespace tropical_elements
  {
    const std::string tn_str_format   = std::string ("%lu");
    const std::string tn_str_infinite = std::string ("-inf");
    const tn_t        tn_infinite     = (1L << 32L);

    number::number ()
    {
      this->n = tn_infinite;
    }

    number::number (tn_t n)
    {
      this->n = n;
    }

    number::~number ()
    {
    }

    bool number::operator! ()
    {
      return !(this->n >> (sizeof (tn_t) * 8 / 2));
    }

    tn_t
    number::get ()
    {
      return this->n;
    }

    number
    number::operator= (tn_t o)
    {
      this->n = o;
      return *this;
    }

    number
    number::operator= (number o)
    {
      this->n = o.n;
      return *this;
    }

    bool
    number::operator== (number o)
    {
      return !(!*this || !o) || (this->n == o.n);
    }

    number number::operator* (number o)
    {
      return number (this->n + o.n);
    }

    number
    number::operator+ (number o)
    {
      tn_t res;
      if (!*this && !o)
      {
        res = this->n > o.n ? this->n : o.n;
      } else
      {
        res = this->n > o.n ? o.n : this->n;
      }
      return number (res);
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
    number::write (FILE *f, file_format format)
    {
      if (f == NULL)
      {
        return;
      }

      if (format != plain_format)
      {
        throw invalid_file_format_exception;
      }

      if (!*this)
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
