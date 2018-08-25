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
    struct element;

    template <typename T>
    struct factor_element : public magma_element<T>
    {
      /** Assigns the factor element the given word.
       * Assigns the factor element the given word.
       * @param [in] w - the word.
       * @return the new value of the factor element.
       */
      virtual T &
      operator= (const element &w) = 0;

      /** Gets a reading of the element.
       * Gets a reading of the element.
       * @return the reading of the element.
       */
      virtual element
      reading () const = 0;

      /** Multiplies two factor elements by using the word concatenation.
       * Multiplies two factor elements by using the word concatenation.
       * @param [in] o - the second element.
       * @return the product of the factor elements.
       */
      T operator* (const T &o) const
      {
        T res = this->reading () * o.reading ();
        return res;
      }
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FACTOR_MONOID_ELEMENT__
