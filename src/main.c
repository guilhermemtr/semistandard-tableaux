#include <stdio.h>
#include "semistandard_tableaux.h"

int
main(int argc, char ** argv)
{
  __pm_matroid_t *m1 = __pm_matroid_read_file("m1");
  __pm_matroid_t *m2 = __pm_matroid_read_file("m2");
  __pm_matroid_t *m_res = __pm_matroid_create();
  __pm_matroid_multiply(m1, m2, m_res);
  __pm_matroid_write_file(m_res, "m_res");
  
  return 0;
}
