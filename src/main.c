#include <stdio.h>
#include "semistandard_tableaux.h"
#include "identity_testing.h"
#include "semistandard_tableaux_pool.h"

void
unit_test_1 ()
{
  printf ("\n\n=== UNIT TEST 1 ===\n\n\n");
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
  printf ("\n\n=== UNIT TEST 2 ===\n\n\n");
  __sst_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1.sst");
  __sst_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2.sst");

  __sst_t *m_res = __sst_tableaux_create ();
  __sst_tableaux_multiply (m1, m2, m_res);


  __sst_tableaux_print (m1);
  printf ("\n\n");
  __sst_tableaux_print (m2);
  printf ("\n\n");
  __sst_tableaux_print (m_res);

  __sst_tableaux_write_plain_file (m_res, "inputs/m_res.sst");
  __sst_tableaux_write_compressed_file (m_res, "inputs/m_res.sstc");
}

static bool
check_identity_dummy (size_t *x,
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
unit_test_3 (char identity[], size_t nr_elems)
{
  printf ("\n\n=== UNIT TEST 3 ===\n\n\n");
  __it_test_identity (identity, NULL, nr_elems, check_identity_dummy);
}


void
unit_test_4 (char identity[])
{
  printf ("\n\n=== UNIT TEST 4 ===\n\n\n");
  __sst_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1.sst");
  __sst_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2.sst");

  __sst_t *m_res = __sst_tableaux_create ();

  __sst_tableaux_multiply (m1, m2, m_res);

  size_t sz_m1    = __sst_tableaux_storage_size (m1);
  size_t sz_m2    = __sst_tableaux_storage_size (m2);
  size_t sz_m_res = __sst_tableaux_storage_size (m_res);

  __sst_word_t w_m1;
  __sst_word_t w_m2;
  __sst_word_t w_m_res;

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

  size_t       nr_elems = 3;
  __sst_word_t elems[nr_elems];
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

void
unit_test_5 ()
{
  printf ("\n\n=== UNIT TEST 5 ===\n\n\n");
  __sst_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1.sst");
  __sst_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2.sst");

  __sst_t *m_res = __sst_tableaux_create ();
  __sst_tableaux_multiply (m1, m2, m_res);

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  __sst_pool_add_tableaux (p, m1);
  __sst_pool_add_tableaux (p, __sst_tableaux_duplicate (m1));
  __sst_pool_add_tableaux (p, m2);
  __sst_pool_add_tableaux (p, __sst_tableaux_duplicate (m1));
  __sst_pool_add_tableaux (p, __sst_tableaux_duplicate (m2));
  __sst_pool_add_tableaux (p, m_res);
  __sst_pool_add_tableaux (p, __sst_tableaux_duplicate (m_res));
  __sst_pool_add_tableaux (p, __sst_tableaux_duplicate (m_res));

  __sst_pool_print (p, __sst_tableaux_print);

  __sst_pool_remove_duplicates (p);

  __sst_pool_print (p, __sst_tableaux_print);
}

void
unit_test_6 ()
{
  printf ("\n\n=== UNIT TEST 6 ===\n\n\n");

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  __sst_pool_add_tableaux_from_directory (p, "./inputs/");

  __sst_pool_print (p, __sst_tableaux_print);

  __sst_pool_remove_duplicates (p);

  __sst_pool_print (p, __sst_tableaux_print);
}


int
main (int argc, char **argv)
{
  unit_test_1 ();
  unit_test_2 ();

  char id1_3[] = "x.y=y.x";
  char id2_3[] = " x.y.z.w = x. y. z . w ";

  unit_test_3 (id1_3, 5L);
  unit_test_3 (id2_3, 3L);

  char id1_4[] = "x.y=y.x";
  char id2_4[] = " x.y.z.w = x. y. z . w ";

  unit_test_4 (id1_4);
  unit_test_4 (id2_4);

  unit_test_5 ();

  unit_test_6 ();

  return 0;
}
