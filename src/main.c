#include <stdio.h>
#include "semistandard_tableaux.h"

int
main (int argc, char **argv)
{
  __tableaux_cell_t cells[10];
  cells[0] = (__tableaux_cell_t){3L, 5L};
  cells[1] = (__tableaux_cell_t){5L, 5L};
  cells[2] = (__tableaux_cell_t){4L, 10L};
  cells[3] = (__tableaux_cell_t){6L, 5L};
  cells[4] = (__tableaux_cell_t){2L, 10L};
  cells[5] = (__tableaux_cell_t){5L, 5L};
  cells[6] = (__tableaux_cell_t){4L, 3L};

  __tableaux_cell_t replaced[50];
  __tableaux_cell_t to_place[50];

  to_place[0] = cells[0];


  __sst_ordered_array_t *arr = malloc (sizeof (__sst_ordered_array_t));
  __sst_ordered_array_create (arr);

  size_t sz = 0;
  print_array (arr);

  for (int i = 0; i < 7; i++)
  {
    printf ("round: %d, sz: %u\n", i, sz);
    printf ("adding: {%u,%u}\n", cells[i].val, cells[i].len);
    if (i == 6)
    {
      printf ("last\n");
    }
    place_cell (arr, cells[i], replaced, &sz);
    print_array (arr);

    printf ("replaced: [");
    size_t j = 0;
    while (j < sz)
    {
      printf ("{%u,%u},", replaced[j].val, replaced[j].len);
      j += replaced[j].len;
    }
    printf ("]\n");
  }

  //__sst_tableaux_t *m1    = __sst_tableaux_read_plain_file ("m1");
  // __sst_tableaux_t *m2    = __sst_tableaux_read_file ("m2");
  // __sst_tableaux_t *m_res = __sst_tableaux_create ();
  // __sst_tableaux_multiply (m1, m2, m_res);
  //__sst_tableaux_write_plain_file (m1, "m1.sst");
  //__sst_tableaux_write_compressed_file (m1, "m1.sstc");
  return 0;
}
