#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"
#include "free_monoid/free_monoid_element.hpp"

using namespace __placid::free_monoid;

TEST (free_monoid_element, test_default_creation)
{
  element e1;

  ASSERT_EQ (e1.length, 0);
}

TEST (free_monoid_element, test_compress)
{
  size_t len1 = 5;

  entry *w1 = new entry[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i].sym   = i;
    w1[i].count = 1;
  }

  element e1;
  e1.word   = w1;
  e1.length = len1;

  e1.compress ();

  ASSERT_EQ (e1.length, len1);

  for (size_t i = 0; i < len1; i++)
  {
    ASSERT_EQ (e1.word[i].sym, i);
    ASSERT_EQ (e1.word[i].count, 1);
  }


  size_t len2    = 20;
  size_t divider = 5;
  entry *w2      = new entry[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i].sym   = i / divider;
    w2[i].count = 1;
  }

  element e2;
  e2.word   = w2;
  e2.length = len2;

  e2.compress ();

  ASSERT_EQ (e2.length, len2 / divider);

  for (size_t i = 0; i < len2 / divider; i++)
  {
    ASSERT_EQ (e2.word[i].sym, i);
    ASSERT_EQ (e2.word[i].count, divider);
  }
}

TEST (free_monoid_element, test_create_from_symbols)
{
  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  element e1 (w1, len1);

  ASSERT_EQ (e1.length, len1);

  for (size_t i = 0; i < len1; i++)
  {
    ASSERT_EQ (e1.word[i].sym, i);
    ASSERT_EQ (e1.word[i].count, 1);
  }


  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

  element e2 (w2, len2);

  e2.compress ();

  ASSERT_EQ (e2.length, len2 / divider);

  for (size_t i = 0; i < len2 / divider; i++)
  {
    ASSERT_EQ (e2.word[i].sym, i);
    ASSERT_EQ (e2.word[i].count, divider);
  }
}

TEST (free_monoid_element, test_create_from_element)
{
  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  element e1 (w1, len1);
  element e11 (e1);

  ASSERT_EQ (e1.length, e11.length);

  for (size_t i = 0; i < len1; i++)
  {
    ASSERT_EQ (e1.word[i].sym, e11.word[i].sym);
    ASSERT_EQ (e1.word[i].count, e11.word[i].count);
  }


  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

  element e2 (w2, len2);
  e2.compress ();

  element e22 (e2);

  ASSERT_EQ (e2.length, e22.length);

  for (size_t i = 0; i < len2 / divider; i++)
  {
    ASSERT_EQ (e2.word[i].sym, e22.word[i].sym);
    ASSERT_EQ (e2.word[i].count, e22.word[i].count);
  }
}

TEST (free_monoid_element, test_assignment)
{
  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  element e1 (w1, len1);
  element e11 = e1;

  ASSERT_EQ (e1.length, e11.length);

  for (size_t i = 0; i < len1; i++)
  {
    ASSERT_EQ (e1.word[i].sym, e11.word[i].sym);
    ASSERT_EQ (e1.word[i].count, e11.word[i].count);
  }
}

TEST (free_monoid_element, test_equality)
{
  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  element e1 (w1, len1);
  element e1_res = e1;

  ASSERT_TRUE (e1 == e1_res);
  ASSERT_FALSE (e1 != e1_res);

  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

  element e2 (w2, len2);
  element e2_res (e2);

  ASSERT_TRUE (e1 != e2);
  ASSERT_FALSE (e1 == e2);

  ASSERT_TRUE (e2 == e2_res);
  ASSERT_FALSE (e2 != e2_res);

  e2.compress ();

  ASSERT_TRUE (e2 == e2_res);
  ASSERT_FALSE (e2 != e2_res);

  ASSERT_TRUE (e2 != e1);
  ASSERT_FALSE (e2 == e1);
}

TEST (free_monoid_element, test_add_symbols)
{
  element e1;

  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  e1.add (w1, len1);

  element e1_res (w1, len1);

  ASSERT_TRUE (e1 == e1_res);

  element e2;

  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

  e2.add (w2, len2);
  element e2_res (e2);

  ASSERT_TRUE (e2 == e2_res);

  element e3 = e1;

  e3.add (w2, len2);

  size_t  len3 = len1 + len2;
  symbol *w3   = new symbol[len3];

  for (size_t i = 0; i < len1; i++)
  {
    w3[i] = w1[i];
  }

  for (size_t i = 0; i < len2; i++)
  {
    w3[i + len1] = w2[i];
  }

  element e3_res (w3, len3);

  ASSERT_TRUE (e3 == e3_res);
}

TEST (free_monoid_element, test_add_entries)
{
  element e1;

  size_t len1 = 5;

  entry * w1 = new entry[len1];
  symbol *s1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    s1[i] = i;
    entry e (s1[i]);
    w1[i] = e;
  }

  e1.add (w1, len1);

  element e1_res (s1, len1);

  ASSERT_TRUE (e1 == e1_res);

  element e2;

  size_t  len2    = 20;
  size_t  divider = 5;
  entry * w2      = new entry[len2];
  symbol *s2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    s2[i] = i / divider;
    entry e (s2[i]);
    w2[i] = e;
  }

  e2.add (w2, len2);
  element e2_res (e2);

  ASSERT_TRUE (e2 == e2_res);

  element e3 = e1;

  e3.add (w2, len2);

  size_t  len3 = len1 + len2;
  entry * w3   = new entry[len3];
  symbol *s3   = new symbol[len3];

  for (size_t i = 0; i < len1; i++)
  {
    s3[i] = s1[i];
    w3[i] = w1[i];
  }

  for (size_t i = 0; i < len2; i++)
  {
    s3[i + len1] = s2[i];
    w3[i + len1] = w2[i];
  }

  element e3_res (s3, len3);

  ASSERT_TRUE (e3 == e3_res);
}

TEST (free_monoid_element, test_mult)
{
  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

  element e1 (w1, len1);
  element e2 (w2, len2);

  element e11_res = e1;
  e11_res.add (w1, len1);

  element e12_res = e1;
  e12_res.add (w2, len2);

  element e21_res = e2;
  e21_res.add (w1, len1);

  element e22_res = e2;
  e22_res.add (w2, len2);

  ASSERT_TRUE (e1 * e1 == e11_res);
  ASSERT_TRUE (e1 * e2 == e12_res);
  ASSERT_TRUE (e2 * e1 == e21_res);
  ASSERT_TRUE (e2 * e2 == e22_res);
}

TEST (free_monoid_element, test_get_size)
{
  element e1;

  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  e1.add (w1, len1);

  ASSERT_EQ (e1.get_size (), len1);

  element e2;

  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

  e2.add (w2, len2);

  ASSERT_EQ (e2.get_size (), len2);

  e2.compress ();

  ASSERT_EQ (e2.get_size (), len2);
}

TEST (free_monoid_element, test_read_plain)
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

TEST (free_monoid_element, test_read_compressed)
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

TEST (free_monoid_element, test_write_plain)
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

TEST (free_monoid_element, test_write_compressed)
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
