#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"
#include "free_monoid/free_monoid_element.hpp"

using namespace __placid::free_monoid;

TEST (free_monoid_element, test_default_creation)
{
  free_monoid_element e1;

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

  free_monoid_element e1;
  e1.word   = w1;
  e1.length = len1;

  e1.compress();
  
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

  free_monoid_element e2;
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
