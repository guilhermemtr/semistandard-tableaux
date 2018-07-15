#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#ifndef __UTILS__
#define __UTILS__

#include "types.h"

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
__utils_str_suffix_match (const char *str, const char *suffix);

/** Function that concatenates a list of strings.
 * Function that concatenates a list of strings.
 * @param n the number of strings to concatenate.
 * @param the other strings, if any.
 * @return the resulting concatenated string.
 */
char *
__utils_concat_strings (const size_t n, ...);

/** Given a filename and the type of the structure, returns a (newly allocated)
 * string with the filename appended with the default suffix of the structure.
 * Given a filename and the type of the structure, returns a (newly allocated)
 * string with the filename appended with the default suffix of the structure.
 * @param filename the filename.
 * @param t the structure type
 * @return the filename with the suffix appended, in a newly allocated string.
 */
char *
__utils_get_filename (const char *filename, enum structure_type t);


#endif    // __UTILS__
