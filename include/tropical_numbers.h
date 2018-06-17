#ifndef __TROPICAL_NUMBERS__
#define __TROPICAL_NUMBERS__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/**
 * Represents a tropical number.
 * The left-most 32 bits are used to represent infinity.
 * The right-most 32 bits are used to represent the number.
 * If two tropical numbers are multiplied, this way of representing tropical
 * numbers ensures that, if at least one of them is infinite, then the result is
 * infinite. On the other hand, if none is infinite, then the result outputs the
 * multiplication of the numbers correctly too.
 */
typedef uint64_t __tn_t;

#define __tn_t_infinite (1L << 32L)



/** Returns if the number is infinite or not.
 * Returns if the number is infinite or not.
 * @param n the tropical number.
 * @return if the number is infinite or not.
 */
bool
__tn_is_infinite (__tn_t n);



/** Returns the value of the tropical number.
 * Returns the value of the tropical number.
 * @param n the tropical number.
 * @return the value of the tropical number.
 */
__tn_t
__tn_get_value (__tn_t n);



/** Returns the sum of two tropical numbers.
 * Returns the sum of two tropical numbers.
 * @param n1 the first tropical number.
 * @param n2 the second tropical number.
 * @return the sum of the two given tropical numbers.
 */
__tn_t
__tn_sum (__tn_t n1, __tn_t n2);


/** Returns the multiplication of two tropical numbers.
 * Returns the multiplication of two tropical numbers.
 * @param n1 the first tropical number.
 * @param n2 the second tropical number.
 * @return the multiplication of the two given tropical numbers.
 */
__tn_t
__tn_mult (__tn_t n1, __tn_t n2);

/** Reads a tropical number from the given FILE stream.
 * Reads a tropical number from the given FILE stream.
 * @param f the file stream.
 * @return the number read.
 */
//__tn_t
//__tn_read (FILE *f);

/** Writes a tropical number to the given FILE stream.
 * Writes a tropical number to the given FILE stream.
 * @param n the tropical number.
 * @param f the file stream.
 */
// void
//__tn_write (__tn_t n, FILE *f);

#endif    // __TROPICAL_NUMBERS__
