#ifndef __PLACID_UTILS__
#define __PLACID_UTILS__

#include <cstdio>
#include <cstdlib>

namespace __placid
{
  /** Function that discards some given number of lines from a file stream.
   * Function that discards some given number of lines from a file stream.
   * @param [in] f - the file stream.
   * @param [in] to_discard - the number of lines to be discarded.
   */
  void
  discard_line (FILE *f, size_t to_discard = 1);

}    // namespace __placid

#endif    // __PLACID_UTILS__
