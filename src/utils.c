#include "utils.h"

#ifdef __UTILS__

// copied from
// https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
bool
str_suffix_match (const char *str, const char *suffix)
{
  if (str == NULL || suffix == NULL)
  {
    return 0;
  }

  size_t lenstr    = strlen (str);
  size_t lensuffix = strlen (suffix);

  if (lensuffix > lenstr)
  {
    return 0;
  }

  return strncmp (str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

#endif    // __UTILS__
