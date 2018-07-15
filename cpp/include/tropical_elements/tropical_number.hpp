#ifndef __PLACID_TROPICAL_NUMBER__
#define __PLACID_TROPICAL_NUMBER__

#include <cstdint>
#include <cassert>

namespace __placid
{
  /**
   * Represents a tropical number.
   * The left-most 32 bits are used to represent infinity.
   * The right-most 32 bits are used to represent the number.
   * If two tropical numbers are multiplied, this way of representing tropical
   * numbers ensures that, if at least one of them is infinite, then the result
   * is infinite. On the other hand, if none is infinite, then the result
   * outputs the multiplication of the numbers correctly too.
   */
  typedef uint64_t tn_t;

  struct tropical_number
  {
    tn_t n;

    tropical_number (tn_t n);

    virtual ~tropical_number ();

    /**
     * Checks if the tropical number if infinite.
     * Returns true if the number is finite, and false if the number is
     * infinite.
     */
    bool operator! ();

    tropical_number
    operator= (tropical_number &o);

    bool
    operator== (tropical_number &o);

    bool
    operator!= (tropical_number &o);

    tropical_number operator* (tropical_number &o);

    tropical_number
    operator+ (tropical_number &o);

    tn_t
    get ();

    static tropical_number
    get_infinite ();
  };

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
