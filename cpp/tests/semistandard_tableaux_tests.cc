#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"

#include "free_monoid/free_monoid_element.hpp"
#include "semistandard_tableaux/ordered_array.hpp"
#include "semistandard_tableaux/semistandard_tableaux.hpp"

using namespace __placid::semistandard_tableaux;

free_monoid::element
get_element_1 ()
{
  size_t len1 = 6;

  free_monoid::symbol *w1 = new free_monoid::symbol[len1];

  w1[0] = 1;
  w1[1] = 3;
  w1[2] = 2;
  w1[3] = 5;
  w1[4] = 4;
  w1[5] = 1;

  return free_monoid::element (w1, len1);
}

free_monoid::element
get_element_2 ()
{
  size_t               len2 = 19;
  free_monoid::symbol *w2   = new free_monoid::symbol[len2];

  w2[0]  = 6;
  w2[1]  = 8;
  w2[2]  = 4;
  w2[3]  = 5;
  w2[4]  = 5;
  w2[5]  = 6;
  w2[6]  = 2;
  w2[7]  = 2;
  w2[8]  = 3;
  w2[9]  = 3;
  w2[10] = 5;
  w2[11] = 7;
  w2[12] = 1;
  w2[13] = 1;
  w2[14] = 1;
  w2[15] = 2;
  w2[16] = 4;
  w2[17] = 4;
  w2[18] = 4;

  return free_monoid::element (w2, len2);
}

TEST (semistandard_tableaux_element, test_default_creation)
{
  size_t   sz = tableaux::default_size;
  tableaux t1;

  ASSERT_TRUE (t1.size == sz);
  ASSERT_TRUE (t1.counter == 0);
  for (size_t i = 0; i < t1.size; i++)
  {
    // just ensuring the row isn't null.
    ASSERT_TRUE (t1.rows[i].size == ordered_array::default_size);
    ASSERT_TRUE (t1.rows[i].counter == 0);
  }

  sz = (1 << 3);
  tableaux t2 (sz);

  ASSERT_TRUE (t2.size == sz);
  ASSERT_TRUE (t2.counter == 0);
  for (size_t i = 0; i < t2.size; i++)
  {
    ASSERT_TRUE (t2.rows[i].size == ordered_array::default_size);
    ASSERT_TRUE (t2.rows[i].counter == 0);
  }
}

TEST (semistandard_tableaux_element, test_creation_from_word)
{
  free_monoid::element e1 = get_element_1 ();
  e1.compress ();

  tableaux t1 (e1);

  // test for t1
  ASSERT_TRUE (t1.rows[0].cells[0].val == 1);
  ASSERT_TRUE (t1.rows[0].cells[0].count == 2);

  ASSERT_TRUE (t1.rows[0].cells[1].val == 4);
  ASSERT_TRUE (t1.rows[0].cells[1].count == 1);

  ASSERT_TRUE (t1.rows[1].cells[0].val == 2);
  ASSERT_TRUE (t1.rows[1].cells[0].count == 1);

  ASSERT_TRUE (t1.rows[1].cells[1].val == 5);
  ASSERT_TRUE (t1.rows[1].cells[1].count == 1);

  ASSERT_TRUE (t1.rows[2].cells[0].val == 3);
  ASSERT_TRUE (t1.rows[2].cells[0].count == 1);

  free_monoid::element e2 = get_element_2 ();
  e2.compress ();

  tableaux t2 (e2);

  // test for t2
  ASSERT_TRUE (t2.rows[0].cells[0].val == 1);
  ASSERT_TRUE (t2.rows[0].cells[0].count == 3);

  ASSERT_TRUE (t2.rows[0].cells[1].val == 2);
  ASSERT_TRUE (t2.rows[0].cells[1].count == 1);

  ASSERT_TRUE (t2.rows[0].cells[2].val == 4);
  ASSERT_TRUE (t2.rows[0].cells[2].count == 3);

  ASSERT_TRUE (t2.rows[1].cells[0].val == 2);
  ASSERT_TRUE (t2.rows[1].cells[0].count == 2);

  ASSERT_TRUE (t2.rows[1].cells[1].val == 3);
  ASSERT_TRUE (t2.rows[1].cells[1].count == 2);

  ASSERT_TRUE (t2.rows[1].cells[2].val == 5);
  ASSERT_TRUE (t2.rows[1].cells[2].count == 1);

  ASSERT_TRUE (t2.rows[1].cells[3].val == 7);
  ASSERT_TRUE (t2.rows[1].cells[3].count == 1);

  ASSERT_TRUE (t2.rows[2].cells[0].val == 4);
  ASSERT_TRUE (t2.rows[2].cells[0].count == 1);

  ASSERT_TRUE (t2.rows[2].cells[1].val == 5);
  ASSERT_TRUE (t2.rows[2].cells[1].count == 2);

  ASSERT_TRUE (t2.rows[2].cells[2].val == 6);
  ASSERT_TRUE (t2.rows[2].cells[2].count == 1);

  ASSERT_TRUE (t2.rows[3].cells[0].val == 6);
  ASSERT_TRUE (t2.rows[3].cells[0].count == 1);

  ASSERT_TRUE (t2.rows[3].cells[1].val == 8);
  ASSERT_TRUE (t2.rows[3].cells[1].count == 1);
}

TEST (semistandard_tableaux_element, test_creation_from_tableaux)
{
  free_monoid::element e1 = get_element_1 ();
  e1.compress ();

  tableaux t1 (e1);

  tableaux t1_copy (t1);

  ASSERT_TRUE (t1_copy.size == t1.size);
  ASSERT_TRUE (t1_copy.counter == t1.counter);

  for (size_t i = 0; i < t1_copy.counter; i++)
  {
    ASSERT_TRUE (t1_copy.rows[i].size == t1.rows[i].size);
    ASSERT_TRUE (t1_copy.rows[i].counter == t1.rows[i].counter);

    for (size_t j = 0; j < t1_copy.rows[i].counter; j++)
    {
      ASSERT_TRUE (t1_copy.rows[i].cells[j] == t1.rows[i].cells[j]);
    }
  }


  free_monoid::element e2 = get_element_2 ();
  e2.compress ();

  tableaux t2 (e2);

  tableaux t2_copy (t2);

  ASSERT_TRUE (t2_copy.size == t2.size);
  ASSERT_TRUE (t2_copy.counter == t2.counter);

  for (size_t i = 0; i < t2_copy.counter; i++)
  {
    ASSERT_TRUE (t2_copy.rows[i].size == t2.rows[i].size);
    ASSERT_TRUE (t2_copy.rows[i].counter == t2.rows[i].counter);

    for (size_t j = 0; j < t2_copy.rows[i].counter; j++)
    {
      ASSERT_TRUE (t2_copy.rows[i].cells[j] == t2.rows[i].cells[j]);
    }
  }
}

TEST (semistandard_tableaux_element, test_assignment_tableaux)
{
  free_monoid::element e1 = get_element_1 ();
  e1.compress ();

  tableaux t1 (e1);

  tableaux t1_copy;
  t1_copy = t1;

  ASSERT_TRUE (t1_copy.counter == t1.counter);

  for (size_t i = 0; i < t1_copy.counter; i++)
  {
    ASSERT_TRUE (t1_copy.rows[i].counter == t1.rows[i].counter);

    for (size_t j = 0; j < t1_copy.rows[i].counter; j++)
    {
      ASSERT_TRUE (t1_copy.rows[i].cells[j] == t1.rows[i].cells[j]);
    }
  }

  free_monoid::element e2 = get_element_2 ();
  e2.compress ();

  tableaux t2 (e2);

  tableaux t2_copy;
  t2_copy = t2;

  ASSERT_TRUE (t2_copy.counter == t2.counter);

  for (size_t i = 0; i < t2_copy.counter; i++)
  {
    ASSERT_TRUE (t2_copy.rows[i].counter == t2.rows[i].counter);

    for (size_t j = 0; j < t2_copy.rows[i].counter; j++)
    {
      ASSERT_TRUE (t2_copy.rows[i].cells[j] == t2.rows[i].cells[j]);
    }
  }
}

TEST (semistandard_tableaux_element, test_assignment_word)
{
  free_monoid::element e1 = get_element_1 ();
  e1.compress ();

  tableaux t1 (e1);

  tableaux t1_copy;
  t1_copy = e1;

  ASSERT_TRUE (t1_copy.counter == t1.counter);

  for (size_t i = 0; i < t1_copy.counter; i++)
  {
    ASSERT_TRUE (t1_copy.rows[i].counter == t1.rows[i].counter);

    for (size_t j = 0; j < t1_copy.rows[i].counter; j++)
    {
      ASSERT_TRUE (t1_copy.rows[i].cells[j] == t1.rows[i].cells[j]);
    }
  }

  free_monoid::element e2 = get_element_2 ();
  e2.compress ();

  tableaux t2 (e2);

  tableaux t2_copy;
  t2_copy = e2;

  ASSERT_TRUE (t2_copy.counter == t2.counter);

  for (size_t i = 0; i < t2_copy.counter; i++)
  {
    ASSERT_TRUE (t2_copy.rows[i].counter == t2.rows[i].counter);

    for (size_t j = 0; j < t2_copy.rows[i].counter; j++)
    {
      ASSERT_TRUE (t2_copy.rows[i].cells[j] == t2.rows[i].cells[j]);
    }
  }
}

TEST (semistandard_tableaux_element, test_equalities)
{
  free_monoid::element e1 = get_element_1 ();

  tableaux t1 (e1);

  e1.compress ();

  tableaux t1_copy (e1);

  ASSERT_TRUE (t1_copy == t1);
  ASSERT_FALSE (t1_copy != t1);

  free_monoid::element e2 = get_element_2 ();

  tableaux t2 (e2);

  e2.compress ();
  tableaux t2_copy (e2);

  ASSERT_TRUE (t2_copy == t2);
  ASSERT_FALSE (t2_copy != t2);

  ASSERT_TRUE (t1 != t2);
  ASSERT_FALSE (t1 == t2);
}

TEST (semistandard_tableaux_element, test_get_size)
{
  free_monoid::element e1 = get_element_1 ();

  e1.compress ();

  tableaux t1 (e1);

  ASSERT_TRUE (t1.get_size () == 6);

  free_monoid::element e2 = get_element_2 ();

  e2.compress ();

  tableaux t2 (e2);

  ASSERT_TRUE (t2.get_size () == 19);
}

TEST (semistandard_tableaux_element, test_get_storage_size)
{
  free_monoid::element e1 = get_element_1 ();

  tableaux t1 (e1);

  ASSERT_TRUE (t1.get_storage_size () == 5);

  free_monoid::element e2 = get_element_2 ();

  tableaux t2 (e2);

  ASSERT_TRUE (t2.get_storage_size () == 12);
}

TEST (semistandard_tableaux_element, test_get_reading)
{
  free_monoid::element e1 = get_element_1 ();

  tableaux t1 (e1);

  tableaux t1_clone (t1.get_reading ());

  ASSERT_TRUE (t1_clone == t1);

  free_monoid::element e2 = get_element_2 ();

  tableaux t2 (e2);

  ASSERT_TRUE (t2.get_storage_size () == 12);
}

TEST (semistandard_tableaux_element, test_append)
{
  free_monoid::element e1 = get_element_1 ();
  free_monoid::element e2 = get_element_2 ();

  tableaux t1 (e1);
  tableaux t2 (e2);

  tableaux t3 (e1 * e2);

  tableaux t12 = t1;

  t12.append (e2);

  ASSERT_TRUE (t12 == t3);
}

TEST (semistandard_tableaux_element, test_multiplication)
{
  free_monoid::element e1 = get_element_1 ();
  free_monoid::element e2 = get_element_2 ();

  tableaux t1 (e1);
  tableaux t2 (e2);

  tableaux t3 (e1 * e2);

  ASSERT_TRUE (t1 * t2 == t3);
}


/*
TEST (semistandard_tableaux_element, test_read_plain)
{
  symbol e0 (0);
  symbol e1 (1);
  symbol e2 (2);
  symbol e3 (3);
  symbol e4 (4);
  symbol e5 (5);

  symbol symbols_1[2]  = {e1, e2};
  symbol symbols_2[5]  = {e0, e1, e2, e3, e4};
  symbol symbols_3[10] = {e0, e1, e1, e1, e2, e3, e4, e4, e5, e5};

  char f1[1 << 10];
  char f2[1 << 10];
  char f3[1 << 10];

  strcpy (f1, "free_monoid_element\n0\n2\n1\n2\n");
  strcpy (f2, "free_monoid_element\n0\n5\n0\n1\n2\n3\n4\n");
  strcpy (f3, "free_monoid_element\n0\n10\n0\n1\n1\n1\n2\n3\n4\n4\n5\n5\n");

  element el1 (symbols_1, 2);
  element el2 (symbols_2, 5);
  element el3 (symbols_3, 10);
  element el1_res (symbols_1, 2);
  element el2_res (symbols_2, 5);
  element el3_res (symbols_3, 10);

  test_magma_element_file_read (el1, f1);
  test_magma_element_file_read (el2, f2);
  test_magma_element_file_read (el3, f3);

  ASSERT_TRUE (el1 == el1_res);
  ASSERT_TRUE (el2 == el2_res);
  ASSERT_TRUE (el3 == el3_res);
}

TEST (semistandard_tableaux_element, test_read_compressed)
{
  symbol e0 (0);
  symbol e1 (1);
  symbol e2 (2);
  symbol e3 (3);
  symbol e4 (4);
  symbol e5 (5);

  symbol symbols_1[2]  = {e1, e2};
  symbol symbols_2[5]  = {e0, e1, e2, e3, e4};
  symbol symbols_3[10] = {e0, e1, e1, e1, e2, e3, e4, e4, e5, e5};

  char f1[1 << 10];
  char f2[1 << 10];
  char f3[1 << 10];

  strcpy (f1, "free_monoid_element\n1\n2\n1 1\n2 1\n");
  strcpy (f2, "free_monoid_element\n1\n5\n0 1\n1 1\n2 1\n3 1\n4 1\n");
  strcpy (f3, "free_monoid_element\n1\n6\n0 1\n1 3\n2 1\n3 1\n4 2\n5 2\n");

  element el1 (symbols_1, 2);
  element el2 (symbols_2, 5);
  element el3 (symbols_3, 10);
  element el1_res (symbols_1, 2);
  element el2_res (symbols_2, 5);
  element el3_res (symbols_3, 10);

  test_magma_element_file_read (el1, f1);
  test_magma_element_file_read (el2, f2);
  test_magma_element_file_read (el3, f3);

  ASSERT_TRUE (el1 == el1_res);
  ASSERT_TRUE (el2 == el2_res);
  ASSERT_TRUE (el3 == el3_res);
}

TEST (semistandard_tableaux_element, test_write_plain)
{
  symbol e0 (0);
  symbol e1 (1);
  symbol e2 (2);
  symbol e3 (3);
  symbol e4 (4);
  symbol e5 (5);

  symbol symbols_1[2]  = {e1, e2};
  symbol symbols_2[5]  = {e0, e1, e2, e3, e4};
  symbol symbols_3[10] = {e0, e1, e1, e1, e2, e3, e4, e4, e5, e5};

  element el1 (symbols_1, 2);
  element el2 (symbols_2, 5);
  element el3 (symbols_3, 10);

  char *el1_res = test_magma_element_file_write (el1, 1 << 10, 0);
  char *el2_res = test_magma_element_file_write (el2, 1 << 10, 0);
  char *el3_res = test_magma_element_file_write (el3, 1 << 10, 0);

  ASSERT_TRUE (strcmp (el1_res, "free_monoid_element\n0\n2\n1\n2\n") == 0);
  ASSERT_TRUE (strcmp (el2_res, "free_monoid_element\n0\n5\n0\n1\n2\n3\n4\n")
               == 0);
  ASSERT_TRUE (
    strcmp (el3_res,
            "free_monoid_element\n0\n10\n0\n1\n1\n1\n2\n3\n4\n4\n5\n5\n")
    == 0);
}

TEST (semistandard_tableaux_element, test_write_compressed)
{
  symbol e0 (0);
  symbol e1 (1);
  symbol e2 (2);
  symbol e3 (3);
  symbol e4 (4);
  symbol e5 (5);

  symbol symbols_1[2]  = {e1, e2};
  symbol symbols_2[5]  = {e0, e1, e2, e3, e4};
  symbol symbols_3[10] = {e0, e1, e1, e1, e2, e3, e4, e4, e5, e5};

  element el1 (symbols_1, 2);
  element el2 (symbols_2, 5);
  element el3 (symbols_3, 10);

  char *el1_res = test_magma_element_file_write (el1, 1 << 10, 1);
  char *el2_res = test_magma_element_file_write (el2, 1 << 10, 1);
  char *el3_res = test_magma_element_file_write (el3, 1 << 10, 1);

  ASSERT_TRUE (strcmp (el1_res, "free_monoid_element\n1\n2\n1 1\n2 1\n") == 0);
  ASSERT_TRUE (
    strcmp (el2_res, "free_monoid_element\n1\n5\n0 1\n1 1\n2 1\n3 1\n4 1\n")
    == 0);
  ASSERT_TRUE (
    strcmp (el3_res,
            "free_monoid_element\n1\n6\n0 1\n1 3\n2 1\n3 1\n4 2\n5 2\n")
    == 0);
}
*/
