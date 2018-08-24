#ifndef __PLACID_RING_ELEMENT__
#define __PLACID_RING_ELEMENT__

#include "magma_element.hpp"

namespace __placid
{
  /**
   * This class defines an abstract ring element.
   * This class defines an abstract ring element.
   * A ring element is an element from a mathematical structure called a ring.
   */
  template <typename T>
  struct ring_element : public magma_element<T>
  {
      public:
    /** Returns the sum of two ring elements.
     * Returns the sum of two ring elements.
     * @param [in] &o the second argument of the sum.
     * @return the sum of the two given ring elements.
     */
    virtual T
    operator+ (const T &o) const = 0;
  };

}    // namespace __placid

#endif    // __PLACID_RING_ELEMENT__
