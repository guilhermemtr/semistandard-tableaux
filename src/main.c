#include <stdio.h>
#include "semistandard_tableaux.h"

void
unit_test_1 ()
{
  __tableaux_cell_t cells[10];
  cells[0] = (__tableaux_cell_t){3L, 5L};
  cells[1] = (__tableaux_cell_t){5L, 5L};
  cells[2] = (__tableaux_cell_t){4L, 10L};
  cells[3] = (__tableaux_cell_t){6L, 5L};
  cells[4] = (__tableaux_cell_t){2L, 10L};
  cells[5] = (__tableaux_cell_t){5L, 5L};
  cells[6] = (__tableaux_cell_t){4L, 3L};

  __tableaux_cell_t to_place[50];
  size_t            to_place_sz = 43L;

  to_place[0]  = cells[0];
  to_place[5]  = cells[1];
  to_place[10] = cells[2];
  to_place[20] = cells[3];
  to_place[25] = cells[4];
  to_place[35] = cells[5];
  to_place[40] = cells[6];


  __tableaux_cell_t replaced[50];
  size_t            sz = 0;

  __sst_ordered_array_t *arr = malloc (sizeof (__sst_ordered_array_t));
  __sst_ordered_array_create (arr);

  print_array (arr);
  __sst_ordered_array_place (arr, to_place, to_place_sz, replaced, &sz);
  print_array (arr);

  printf ("[");
  for (size_t j = 0; j < sz; j += replaced[j].len)
  {
    printf ("{%lu,%lu},", replaced[j].val, replaced[j].len);
  }
  printf ("]\n");
}

void
unit_test_2 ()
{
  __sst_tableaux_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1");
  __sst_tableaux_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2");

  __sst_tableaux_t *m_res = __sst_tableaux_create ();
  __sst_tableaux_multiply (m1, m2, m_res);


  __sst_tableaux_print (m1);
  printf("\n\n");
  __sst_tableaux_print (m2);
  printf("\n\n");
  __sst_tableaux_print (m_res);

  __sst_tableaux_write_plain_file (m_res, "m_res.sst");
  __sst_tableaux_write_compressed_file (m_res, "m_res.sstc");
}


int
main (int argc, char **argv)
{
  unit_test_2 ();
  return 0;
}
