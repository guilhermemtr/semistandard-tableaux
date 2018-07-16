#include "tropical_number.hpp"

#ifdef __PLACID_TROPICAL_NUMBER__

namespace __placid
{
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

  tropical_number
  tropical_number::operator= (tropical_number &o)
  {
    this->n = o.n;
    return *this;
  }

  bool
  tropical_number::operator== (tropical_number &o)
  {
    return (!*this && !o) || (this->n == o.n);
  }

  bool
  tropical_number::operator!= (tropical_number &o)
  {
    return !(*this == o);
  }

  tropical_number tropical_number::operator* (tropical_number &o)
  {
    return tropical_number (this->n + o.n);
  }
  
    #include<stdio.h>
  tropical_number
  tropical_number::operator+ (tropical_number &o)
  {
    tn_t res;
    if (!*this && !o)
    {
      res = this->n > o.n ? this->n : o.n;
    } else
    {
      res = this->n > o.n ? o.n : this->n;
    }
    printf("%lu\n",res);
    return tropical_number (res);
  }

  tn_t
  tropical_number::get ()
  {
    return this->n;
  }

  tropical_number
  tropical_number::get_infinite ()
  {
    return tropical_number (1L << 32L);
  }

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
