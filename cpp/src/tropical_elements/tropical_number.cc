#include "tropical_number.hpp"

#ifdef __PLACID_TROPICAL_NUMBER__

namespace __placid
{
  const std::string tn_str_format   = std::string ("%lu");
  const std::string tn_str_infinite = std::string ("-inf");
  const tn_t        tn_infinite     = (1L << 32L);

  tropical_number::tropical_number ()
  {
    this->n = tn_infinite;
  }

  tropical_number::tropical_number (tn_t n)
  {
    this->n = n;
  }

  tropical_number::~tropical_number ()
  {
  }

  bool tropical_number::operator! ()
  {
    return !(this->n >> (sizeof (tn_t) * 8 / 2));
  }

  tn_t
  tropical_number::get ()
  {
    return this->n;
  }

  tropical_number
  tropical_number::operator= (tn_t o)
  {
    this->n = o;
    return *this;
  }

  tropical_number
  tropical_number::operator= (tropical_number o)
  {
    this->n = o.n;
    return *this;
  }

  bool
  tropical_number::operator== (tropical_number o)
  {
    return !(!*this || !o) || (this->n == o.n);
  }

  tropical_number tropical_number::operator* (tropical_number o)
  {
    return tropical_number (this->n + o.n);
  }

  tropical_number
  tropical_number::operator+ (tropical_number o)
  {
    tn_t res;
    if (!*this && !o)
    {
      res = this->n > o.n ? this->n : o.n;
    } else
    {
      res = this->n > o.n ? o.n : this->n;
    }
    return tropical_number (res);
  }

  void
  tropical_number::read (FILE *f)
  {
    char val[256];
    if (fscanf (f, "%256s", val) != 1)
    {
      throw invalid_file_format_exception;
    }

    tn_t v;

    if (strcmp (tn_str_infinite.c_str (), val) == 0)
    {
      v = tropical_number ().get ();
    } else
    {
      v = atoll (val);
    }

    this->n = v;
  }

  void
  tropical_number::write (FILE *f, file_format format)
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

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
