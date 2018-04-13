#include <stdio.h>
#include "semistandard_tableaux.h"

int
main(int argc, char ** argv)
{
  __sst_tableaux_t *m1 = __sst_tableaux_read_file("m1");
  __sst_tableaux_t *m2 = __sst_tableaux_read_file("m2");
  __sst_tableaux_t *m_res = __sst_tableaux_create();
  __sst_tableaux_multiply(m1, m2, m_res);
  __sst_tableaux_write_file(m_res, "m_res");
  
  return 0;
}
