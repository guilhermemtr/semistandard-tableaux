#ifndef __PLACID_TROPICAL_NUMBER__
#define __PLACID_TROPICAL_NUMBER__

#include <cstdint>
#include <cassert>

#include "ring_element.hpp"

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

  const tn_t tn_infinite (1L << 32L);

  struct tropical_number : ring_element
  {
    tn_t n;

    /** Constructs a new tropical number, given its value.
     * Constructs a new tropical number, given its value.
     * @param n the number of the tropical number to be created.
     */
    tropical_number (tn_t n);

    /** Destroys a tropical number structure.
     * Destroys a tropical number structure.
     */
    virtual ~tropical_number ();

    /** Checks if the tropical number if infinite.
     * Checks if the tropical number if infinite.
     * @return true if the number is finite, and false otherwise.
     */
    bool operator! ();

    /** Makes an assignment of tropical numbers, given a tropical number.
     * Makes an assignment of tropical numbers, given a tropical number.
     * @param &o the tropical number to assign.
     * @return the tropical number value assigned.
     */
    tropical_number
    operator= (tropical_number &o);

    /** Makes an assignment of tropical numbers, given a tropical number integer
     * value. Makes an assignment of tropical numbers, given a tropical number
     * integer value.
     * @param &o the tropical number integer value to assign.
     * @return the tropical number value assigned.
     */
    tropical_number
    operator= (tn_t &o);

    /** Checks if two tropical numbers are equal.
     * Checks if two tropical numbers are equal.
     * @param &o the second argument of the equality.
     * @return whether the tropical numbers are equal or not.
     */
    bool
    operator== (tropical_number &o);

    /** Checks if two tropical numbers are different.
     * Checks if two tropical numbers are different.
     * @param &o the second argument of the inequality.
     * @return whether the tropical numbers are different or not.
     */
    bool
    operator!= (tropical_number &o);

    /** Returns the multiplication of two tropical numbers.
     * Returns the multiplication of two tropical numbers.
     * @param &o the second argument of the multiplication.
     * @return the multiplication of the two given tropical numbers.
     */
    tropical_number operator* (tropical_number &o);

    /** Returns the sum of two tropical numbers.
     * Returns the sum of two tropical numbers.
     * @param &o the second argument of the sum.
     * @return the sum of the two given tropical numbers.
     */
    tropical_number
    operator+ (tropical_number &o);

    /** Returns the value of the tropical number.
     * Returns the value of the tropical number.
     * @return the value of the tropical number.
     */
    tn_t
    get ();

    /** Returns the tropical number representing -infinity.
     * Returns the tropical number representing -infinity.
     * @return the tropical number -infinity.
     */
    static tropical_number
    get_infinite ();
  };

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
