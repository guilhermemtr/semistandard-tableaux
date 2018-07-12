#include "utils.h"

#ifdef __UTILS__

// copied from
// https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
bool
__utils_str_suffix_match (const char *str, const char *suffix)
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

char *
__utils_concat_strings (const size_t n, ...)
{
  char *strs[n];

  va_list arg_ptr;
  va_start (arg_ptr, n);
  for (size_t i = 0; i < n; i++)
  {
    strs[i] = va_arg (arg_ptr, char *);
  }
  va_end (arg_ptr);

  size_t len = 0;
  for (size_t i = 0; i < n; i++)
  {
    len += strlen (strs[i]);
  }

  char *res = malloc ((len + 1) * sizeof (char));

  size_t offset = 0;
  for (size_t i = 0; i < n; i++)
  {
    strcpy (res, strs[i]);
    offset += strlen (strs[i]);
  }

  return res;
}


char *
__utils_get_filename (const char *filename, enum structure_type t)
{
  const char *suffix = get_structure_type_string (t);
  return __utils_concat_strings (3, filename, ".", suffix);
}

#endif    // __UTILS__
