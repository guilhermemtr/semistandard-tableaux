#ifndef __PLACID_RING_ELEMENT__
#define __PLACID_RING_ELEMENT__

#include "magma_element.hpp"

namespace __placid
{
  template <typename T>
  class ring_element : public magma_element<T>
  {
      public:
    /** Returns the sum of two ring elements.
     * Returns the sum of two ring elements.
     * @param &o the second argument of the sum.
     * @return the sum of the two given ring elements.
     */
    virtual T
    operator+ (T &o) = 0;
  };

}    // namespace __placid

#endif    // __PLACID_RING_ELEMENT__
