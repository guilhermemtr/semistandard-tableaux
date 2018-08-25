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

    extern const std::string
      tn_str_format;    // !< represents the format of a tropical number.
    extern const std::string
      tn_str_infinite;    // !< represents the notation used to denote an
                          // infinite value of a tropical number as a string.
    extern const tn_t
      tn_infinite;    // !< represents the smallest number corresponding to
                      // infinity. Every number larger than tn_infinite is also
                      // infinite.

    /**
     * This class defines a tropical number.
     * This class defines a tropical number.
     */
    struct number : public ring_element<number>
    {
      static const file_format plain_format =
        0;    // !< represents the format corresponding to the plain format of
              // the tropical number.

      tn_t n;    // !< represents the tropical number.

      /** Constructs a new tropical number, corresponding to -infinity.
       * Constructs a new tropical number, corresponding to -infinity.
       */
      number ();

      /** Constructs a new tropical number, given its value.
       * Constructs a new tropical number, given its value.
       * @param [in] n the number of the tropical number to be created.
       */
      number (const tn_t &n);

      /** Constructs a new tropical number, given another tropical number.
       * Constructs a new tropical number, given another tropical number.
       * @param [in] &o the other tropical number.
       */
      number (const number &o);

      /** Destroys a tropical number structure.
       * Destroys a tropical number structure.
       */
      virtual ~number ();

      /** Returns the value of the tropical number.
       * Returns the value of the tropical number.
       * @return the value of the tropical number.
       */
      tn_t
      get () const;

      /** Checks if the tropical number if infinite.
       * Checks if the tropical number if infinite.
       * @return true if the number is finite, and false otherwise.
       */
      bool
      finite () const;

      /** Makes an assignment of tropical numbers, given a tropical number
       * integer value. Makes an assignment of tropical numbers, given a
       * tropical number integer value.
       * @param [in] &o the tropical number integer value to assign.
       * @return the tropical number value assigned.
       */
      number &
      operator= (const tn_t &o);

      number &
      operator= (const number &o);

      bool
      operator== (const number &o) const;

      number operator* (const number &o) const;

      number
      operator+ (const number &o) const;

      void
      read (FILE *f);

      void
      write (FILE *f, file_format format = 0) const;
    };

  }    // namespace tropical_elements

}    // namespace __placid

#endif    // __PLACID_TROPICAL_NUMBER__
