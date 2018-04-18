#include <stdio.h>
#include "semistandard_tableaux.h"
#include "identity_testing.h"

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
  printf ("\n\n");
  __sst_tableaux_print (m2);
  printf ("\n\n");
  __sst_tableaux_print (m_res);

  __sst_tableaux_write_plain_file (m_res, "m_res.sst");
  __sst_tableaux_write_compressed_file (m_res, "m_res.sstc");
}

static bool
check_identity (size_t *x,
                size_t  len_x,
                size_t *y,
                size_t  len_y,
                size_t *assigns,
                size_t  nr_vars,
                void *  elems)
{
  printf ("Assignment:\t");
  for (size_t i = 0; i < nr_vars; i++)
  {
    printf ("%lu,", assigns[i]);
  }
  printf ("\n");
  return true;
}

void
unit_test_3 (char identity[])
{
  __sst_tableaux_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1");
  __sst_tableaux_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2");

  __sst_tableaux_t *m_res = __sst_tableaux_create ();

  __sst_tableaux_multiply (m1, m2, m_res);

  size_t sz_m1    = __sst_tableaux_storage_size (m1);
  size_t sz_m2    = __sst_tableaux_storage_size (m2);
  size_t sz_m_res = __sst_tableaux_storage_size (m_res);

  __sst_word_tableaux_t w_m1;
  __sst_word_tableaux_t w_m2;
  __sst_word_tableaux_t w_m_res;

  __tableaux_cell_t m1_cells[sz_m1];
  __tableaux_cell_t m2_cells[sz_m2];
  __tableaux_cell_t m_res_cells[sz_m_res];

  w_m1.cells    = m1_cells;
  w_m2.cells    = m2_cells;
  w_m_res.cells = m_res_cells;

  w_m1.counter = w_m1.size =
    __sst_tableaux_read_to_compressed_tableaux (m1, w_m1.cells);
  w_m2.counter = w_m2.size =
    __sst_tableaux_read_to_compressed_tableaux (m2, w_m2.cells);
  w_m_res.counter = w_m_res.size =
    __sst_tableaux_read_to_compressed_tableaux (m_res, w_m_res.cells);

  size_t                nr_elems = 3;
  __sst_word_tableaux_t elems[nr_elems];
  elems[0] = w_m1;
  elems[1] = w_m2;
  elems[2] = w_m_res;

  printf ("Verifying identity \"%s\".\n", identity);
  bool res = __it_test_identity (
    identity, elems, nr_elems, __sst_tableaux_check_identity);
  if (res)
  {
    printf ("Identity verified.\n");
  } else
  {
    printf ("Identity does not hold.\n");
  }
}

int
main (int argc, char **argv)
{
  char id1[] = "x.y=y.x";
  char id2[] = " x.y.z.w = x. y. z . w ";
  unit_test_3 (id1);
  unit_test_3 (id2);
  return 0;
}
