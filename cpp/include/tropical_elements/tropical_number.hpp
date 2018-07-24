#ifndef __PLACID_TROPICAL_NUMBER__
#define __PLACID_TROPICAL_NUMBER__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>

#include "ring_element.hpp"

namespace __placid
{
  namespace tropical_elements
  {
    /**
     * Represents a tropical number.
     * The left-most 32 bits are used to represent infinity.
     * The right-most 32 bits are used to represent the number.
     * If two tropical numbers are multiplied, this way of representing tropical
     * numbers ensures that, if at least one of them is infinite, then the
     * result is infinite. On the other hand, if none is infinite, then the
     * result outputs the multiplication of the numbers correctly too.
     */
    typedef uint64_t tn_t;

    extern const std::string tn_str_format;
    extern const std::string tn_str_infinite;
    extern const tn_t        tn_infinite;

    struct number : public ring_element<number>
    {
      static const file_format plain_format = 0;

      tn_t n;

      /** Constructs a new tropical number, corresponding to -infinity.
       * Constructs a new tropical number, corresponding to -infinity.
       */
      number ();

      /** Constructs a new tropical number, given its value.
       * Constructs a new tropical number, given its value.
       * @param n the number of the tropical number to be created.
       */
      number (tn_t n);

      /** Destroys a tropical number structure.
       * Destroys a tropical number structure.
       */
      virtual ~number ();

      /** Returns the value of the tropical number.
       * Returns the value of the tropical number.
       * @return the value of the tropical number.
       */
      tn_t
      get ();

      /** Checks if the tropical number if infinite.
       * Checks if the tropical number if infinite.
       * @return true if the number is finite, and false otherwise.
       */
      bool operator! ();

      /** Makes an assignment of tropical numbers, given a tropical number
       * integer value. Makes an assignment of tropical numbers, given a
       * tropical number integer value.
       * @param &o the tropical number integer value to assign.
       * @return the tropical number value assigned.
       */
      number
      operator= (tn_t o);

      number
      operator= (number o);

      bool
      operator== (number o);

      number operator* (number o);

      number
      operator+ (number o);

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format = 0);
    };

  }    // namespace tropical_elements

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
