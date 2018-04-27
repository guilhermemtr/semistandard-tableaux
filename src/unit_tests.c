#include "unit_tests.h"

static void
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

  __sst_ordered_array_print (arr);
  __sst_ordered_array_place (arr, to_place, to_place_sz, replaced, &sz);
  __sst_ordered_array_print (arr);

  printf ("[");
  for (size_t j = 0; j < sz; j += replaced[j].len)
  {
    printf ("{%lu,%lu},", replaced[j].val, replaced[j].len);
  }
  printf ("]\n");
}

static void
unit_test_2 ()
{
  printf ("\n\n=== UNIT TEST 2 ===\n\n\n");
  __sst_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1.sst");
  __sst_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2.sst");
  __sst_t *m3 = __sst_tableaux_read_table_file ("inputs/m3.sstt");

  __sst_t *m_res = __sst_tableaux_create ();
  __sst_tableaux_multiply (m1, m2, m_res);


  __sst_tableaux_plain_print (m1);
  printf ("\n\n");
  __sst_tableaux_plain_print (m2);
  printf ("\n\n");
  __sst_tableaux_plain_print (m_res);
  printf ("\n\n");
  __sst_tableaux_plain_print (m3);
  __sst_tableaux_write_table_file (m3, "m3.sstt");
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

static void
unit_test_3 (char identity[], size_t nr_elems)
{
  printf ("\n\n=== UNIT TEST 3 ===\n\n\n");
  __it_test_identity (identity, NULL, nr_elems, check_identity_dummy, NULL);
}


static void
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

  size_t        nr_elems = 3;
  __sst_word_t *elems[nr_elems];
  elems[0] = &w_m1;
  elems[1] = &w_m2;
  elems[2] = &w_m_res;

  __it_assignment_t *counter_example;

  printf ("Verifying identity \"%s\".\n", identity);
  bool res = __it_test_identity (
    identity, elems, nr_elems, __sst_tableaux_check_identity, &counter_example);
  if (res)
  {
    printf ("Identity passes tests.\n");
  } else
  {
    printf ("Identity does not hold.\n");
  }
}

static void
unit_test_5 ()
{
  printf ("\n\n=== UNIT TEST 5 ===\n\n\n");
  __sst_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1.sst");

  __sst_tableaux_print (m1);
  printf ("\n");

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  __sst_pool_add_word_tableaux (p, __sst_tableaux_word_create (m1));

  printf ("\n");
  __sst_pool_print (p, __sst_tableaux_word_to_table_print);
  printf ("\n");

  __sst_t *m11 = __sst_tableaux_table_create (p->tableaux[0]);
  __sst_pool_add_word_tableaux (p, __sst_tableaux_word_create (m11));

  printf ("\n");
  __sst_pool_print (p, __sst_tableaux_word_to_table_print);
  printf ("\n");
}

static void
unit_test_6 ()
{
  printf ("\n\n=== UNIT TEST 6 ===\n\n\n");
  __sst_t *m1 = __sst_tableaux_read_plain_file ("inputs/m1.sst");
  __sst_t *m2 = __sst_tableaux_read_plain_file ("inputs/m2.sst");

  __sst_t *m_res = __sst_tableaux_create ();
  __sst_tableaux_multiply (m1, m2, m_res);

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  __sst_pool_add_word_tableaux (p, __sst_tableaux_word_create (m1));
  __sst_pool_add_word_tableaux (
    p, __sst_tableaux_word_create (__sst_tableaux_duplicate (m1)));
  __sst_pool_add_word_tableaux (p, __sst_tableaux_word_create (m2));
  __sst_pool_add_word_tableaux (
    p, __sst_tableaux_word_create (__sst_tableaux_duplicate (m1)));
  __sst_pool_add_word_tableaux (
    p, __sst_tableaux_word_create (__sst_tableaux_duplicate (m2)));
  __sst_pool_add_word_tableaux (p, __sst_tableaux_word_create (m_res));
  __sst_pool_add_word_tableaux (
    p, __sst_tableaux_word_create (__sst_tableaux_duplicate (m_res)));
  __sst_pool_add_word_tableaux (
    p, __sst_tableaux_word_create (__sst_tableaux_duplicate (m_res)));

  __sst_pool_print (p, __sst_tableaux_word_to_table_print);

  __sst_pool_remove_duplicates (p);

  __sst_pool_print (p, __sst_tableaux_word_to_table_print);
}

static void
unit_test_7 ()
{
  printf ("\n\n=== UNIT TEST 7 ===\n\n\n");

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  __sst_pool_add_tableaux_from_directory (p, "./inputs/");

  __sst_pool_print (p, __sst_tableaux_word_to_table_print);

  __sst_pool_remove_duplicates (p);

  __sst_pool_print (p, __sst_tableaux_word_to_table_print);
}

static void
unit_test_8 ()
{
  printf ("\n\n=== UNIT TEST 8 ===\n\n\n");

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  __sst_pool_add_tableaux_from_directory (p, "./inputs/");

  char id_2[] = "x=x";
  char id_3[] = "x.y=y.x";

  __sst_pool_remove_duplicates (p);
  //  __sst_pool_t *p_2 = __sst_pool_create_sst_index_pool (p, 2);
  //  __sst_pool_t *p_3 = __sst_pool_create_sst_index_pool (p, 3);

  __sst_pool_print (p, __sst_tableaux_word_to_table_print);

  __it_assignment_t *counter_example_id_2;
  bool id_1_check = __sst_pool_test_identity (p, id_2, &counter_example_id_2);

  if (id_1_check)
  {
    printf ("Identity 1 passes tests.\n");
  } else
  {
    printf ("Identity 1 does not hold.\n");
    printf ("Identity does not hold for values:\n");
    for (size_t i = 0; i < counter_example_id_2->counter; i++)
    {
      printf ("%s set to:\n", counter_example_id_2->variables[i]);
      __sst_tableaux_word_to_table_plain_print (
        p->tableaux[counter_example_id_2->entries[i]]);
    }
  }

  __it_assignment_t *counter_example_id_3;

  bool id_2_check = __sst_pool_test_identity (p, id_3, &counter_example_id_3);

  if (id_2_check)
  {
    printf ("Identity 2 passes tests.\n");
  } else
  {
    printf ("Identity 2 does not hold.\n\n");

    printf ("Identity does not hold for values:\n\n\n");
    for (size_t i = 0; i < counter_example_id_3->counter; i++)
    {
      printf ("%s set to:\n\n", counter_example_id_3->variables[i]);
      __sst_tableaux_word_to_table_plain_print (
        p->tableaux[counter_example_id_3->entries[i]]);
      printf ("\n");
    }
  }

  //__sst_pool_print (p, __sst_tableaux_word_to_table_print);


  //__sst_pool_print (p, __sst_tableaux_word_to_table_print);
}

static void
unit_test_9 ()
{
  printf ("\n\n=== UNIT TEST 9 ===\n\n\n");

  __sst_pool_t *p = __sst_pool_create_sst_pool ();

  printf ("READING\n");
  __sst_pool_add_tableaux_from_directory (p, "./inputs/random/");
  printf ("%lu\n", p->counter);
  printf ("REMOVING DUPS\n");
  __sst_pool_remove_duplicates (p);
  printf ("REDUCING TO INDEX 2\n");
  __sst_pool_t *p2 = __sst_pool_create_sst_index_pool (p, 2);

  printf ("%lu\n", p2->counter);

  char               id_2[] = "p.q.p.q.p.q=p.q.q.p.p.q";
  __it_assignment_t *counter_example_id_2;
  bool id_2_check = __sst_pool_test_identity (p2, id_2, &counter_example_id_2);

  if (id_2_check)
  {
    printf ("Identity 2 passes tests.\n");
  } else
  {
    printf ("Identity 2 does not hold.\n\n");

    printf ("Identity does not hold for values:\n\n\n");
    for (size_t i = 0; i < counter_example_id_2->counter; i++)
    {
      printf ("%s set to:\n\n", counter_example_id_2->variables[i]);
      __sst_tableaux_word_to_table_plain_print (
        p2->tableaux[counter_example_id_2->entries[i]]);
      printf ("\n");
    }
  }
}

int
run_tests ()
{
  /*init_logger();
  set_log_file("log");

  log(YAL_ERROR, "Error not showing up %s\n", "error 1");
  set_lvl_err();
  log(YAL_ERROR, "Error now showing up %s\n", "error 2");

  log(YAL_WARN, "Warning not showing up %s\n", "warning 1");
  set_lvl_warn();
  log(YAL_WARN, "Warning now showing up %s\n", "warning 2");


  log(YAL_DBG, "Debug info not showing up %s\n", "debug info 1");
  set_lvl_dbg();
  log(YAL_DBG, "Debug info now showing up %s\n", "debug info 2");

  
  log(YAL_INFO, "Info not showing up %s\n", "info 1");
  set_lvl_info();
  log(YAL_INFO, "Info now showing up %s\n", "info 2");
  close_log_file();*/

  
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

  unit_test_7 ();

  unit_test_8 ();

  unit_test_9 ();

  return 0;
}
