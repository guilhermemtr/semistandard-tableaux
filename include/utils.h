#include <stdbool.h>
#include <string.h>

#ifndef __UTILS__
#define __UTILS__

// copied from
// https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
/**
 * Checks if a string ends with a certain suffix.
 * Checks if a string ends with a certain suffix.
 * @param str the string
 * @param suffix the suffix
 * @return whether the string ends with the given suffix or not.
 */
bool
str_suffix_match (const char *str, const char *suffix);

#endif    // __UTILS__
