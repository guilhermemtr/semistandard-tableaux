#ifndef __PLACID_FACTOR_MONOID_ELEMENT__
#define __PLACID_FACTOR_MONOID_ELEMENT__

#include <string>

#include <cstdio>
#include <cerrno>
#include <cstdint>

#include "config.hpp"

#include "magma_element.hpp"
#include "free_monoid_element.hpp"

namespace __placid
{
  namespace free_monoid
  {
    template <typename T>
    struct factor_element : public magma_element<T>
    {
      virtual T &
      operator= (const element &w) = 0;

      virtual element
      reading () const = 0;

      T operator* (const T &o) const
      {
        T res = this->reading () * o.reading ();
        return res;
      }
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FACTOR_MONOID_ELEMENT__
