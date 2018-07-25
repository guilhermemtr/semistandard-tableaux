#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"
#include "free_monoid/free_monoid_element.hpp"

using namespace __placid::free_monoid;

TEST (element, test_default_creation)
{
  element e1;

  ASSERT_EQ (e1.length, 0);
}

TEST (element, test_compress)
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

TEST (element, test_create_from_symbols)
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

TEST (element, test_create_from_element)
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


TEST (element, test_assignment)
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

TEST (element, test_equality)
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

TEST (element, test_add)
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

  element e3 = e2;
  e3.add (w1, len1);

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

TEST (element, test_mult)
{
  size_t len1 = 5;

  symbol *w1 = new symbol[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i] = i;
  }

  element e1 (w1, len1);

  size_t  len2    = 20;
  size_t  divider = 5;
  symbol *w2      = new symbol[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i] = i / divider;
  }

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
