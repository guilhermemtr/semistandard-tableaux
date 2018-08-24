#ifndef __PLACID_UTILS__
#define __PLACID_UTILS__

#include <cstdio>

namespace __placid
{
  void
  discard_line (FILE *f, size_t to_discard = 1)
  {
    char * tmp = NULL;
    size_t len = 0;
    for (size_t i = 0; i < to_discard; i++)
    {
      getline (&tmp, &len, f);
      free (tmp);
      tmp = NULL;
    }
  }

}    // namespace __placid

#endif    // __PLACID_UTILS__
