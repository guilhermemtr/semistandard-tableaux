#ifndef __PLACID_RING_ELEMENT__
#define __PLACID_RING_ELEMENT__

#include "magma_element.hpp"

namespace __placid
{
  class ring_element : public magma_element
  {
      public:
    /** Returns the sum of two ring elements.
     * Returns the sum of two ring elements.
     * @param &o the second argument of the sum.
     * @return the sum of the two given ring elements.
     */
    magma_element
    operator+ (magma_element &o);
  };

}    // namespace __placid

#endif    // __PLACID_RING_ELEMENT__
