#include <gtest/gtest.h>

#include "tuple.hpp"
#include "magma_element_test_utils.hpp"
#include "semistandard_tableaux/tableaux_entry.hpp"
#include "semistandard_tableaux/ordered_array.hpp"

using namespace __placid::semistandard_tableaux;

TEST (ordered_array, test_creation_default)
{
  ordered_array o1;

  ASSERT_TRUE (o1.size == ordered_array::default_size);
  ASSERT_TRUE (o1.counter == 0);
  for (size_t i = 0; i < o1.size; i++)
  {
    ASSERT_EQ (o1.cells[i].val, 0);
    ASSERT_EQ (o1.cells[i].count, 0);
  }
}

// tests constructor given ordered array and assignment of ordered arrays.
TEST (ordered_array, test_copy)
{
  ordered_array o1;

  o1.counter = o1.size / 2;
  for (size_t i = 0; i < o1.counter; i++)
  {
    o1.cells[i].val   = i;
    o1.cells[i].count = i * i;
  }

  ordered_array o2;
  o2.copy (o1);

  ASSERT_TRUE (o2.size == o1.size);
  ASSERT_TRUE (o2.counter == o1.counter);

  for (size_t i = 0; i < o2.counter; i++)
  {
    ASSERT_EQ (o2.cells[i].val, o1.cells[i].val);
    ASSERT_EQ (o2.cells[i].count, o1.cells[i].count);
  }

  for (size_t i = o2.counter; i < o2.size; i++)
  {
    ASSERT_EQ (o2.cells[i].val, 0);
    ASSERT_EQ (o2.cells[i].count, 0);
  }
}

TEST (ordered_array, test_compress)
{
  size_t len1 = 5;

  entry *w1 = new entry[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i].val   = i;
    w1[i].count = 1;
  }

  ordered_array e1;
  e1.cells   = w1;
  e1.size    = len1;
  e1.counter = len1;

  e1.compress ();

  ASSERT_EQ (e1.counter, len1);
  ASSERT_EQ (e1.size, len1);

  for (size_t i = 0; i < len1; i++)
  {
    ASSERT_EQ (e1.cells[i].val, i);
    ASSERT_EQ (e1.cells[i].count, 1);
  }


  size_t len2    = 20;
  size_t divider = 5;
  entry *w2      = new entry[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i].val   = i / divider;
    w2[i].count = 1;
  }

  ordered_array e2;
  e2.cells   = w2;
  e2.size    = len2;
  e2.counter = len2;

  e2.compress ();

  ASSERT_EQ (e2.counter, len2 / divider);
  ASSERT_EQ (e2.size, len2);

  for (size_t i = 0; i < len2 / divider; i++)
  {
    ASSERT_EQ (e2.cells[i].val, i);
    ASSERT_EQ (e2.cells[i].count, divider);
  }
}

TEST (ordered_array, test_equality)
{
  ordered_array o1;
  ordered_array o2 (o1);

  ASSERT_TRUE (o1 == o2);
  ASSERT_FALSE (o1 != o2);

  o1.counter = o1.size / 2;
  for (size_t i = 0; i < o1.counter; i++)
  {
    o1.cells[i].val   = i;
    o1.cells[i].count = i * i;
  }

  ASSERT_TRUE (o1 != o2);
  ASSERT_FALSE (o1 == o2);

  o2 = o1;

  ASSERT_TRUE (o1 == o2);
  ASSERT_FALSE (o1 != o2);

  size_t len1 = 5;

  entry *w1 = new entry[len1];
  for (size_t i = 0; i < len1; i++)
  {
    w1[i].val   = i;
    w1[i].count = 1;
  }

  o1.cells   = w1;
  o1.size    = len1;
  o1.counter = len1;

  ordered_array o3 (o1);

  ASSERT_TRUE (o1 == o3);
  ASSERT_FALSE (o1 != o3);

  o1.compress ();

  ASSERT_TRUE (o1 == o3);
  ASSERT_FALSE (o1 != o3);

  size_t len2    = 20;
  size_t divider = 5;
  entry *w2      = new entry[len2];

  for (size_t i = 0; i < len2; i++)
  {
    w2[i].val   = i / divider;
    w2[i].count = 1;
  }

  o2.cells   = w2;
  o2.size    = len2;
  o2.counter = len2;

  ordered_array o4 (o2);

  ASSERT_TRUE (o2 == o4);
  ASSERT_FALSE (o2 != o4);

  o4.compress ();

  ASSERT_TRUE (o2 == o4);
  ASSERT_FALSE (o2 != o4);
}

TEST (ordered_array, test_get_size)
{
  ordered_array o1;
  ASSERT_TRUE (o1.get_size () == 0);

  o1.counter = o1.size / 2;
  for (size_t i = 0; i < o1.counter; i++)
  {
    o1.cells[i].val   = i;
    o1.cells[i].count = i;
  }

  ASSERT_TRUE (o1.get_size () == ((o1.counter - 1) * o1.counter) / 2);
}

// To test: add, write and read.
// How to write and read?
// Write for ordered array not yet implemented.

TEST (ordered_array, test_add)
{
  entry *cells = new entry[10];
  cells[0]     = entry (3L, 5L);
  cells[1]     = entry (5L, 5L);
  cells[2]     = entry (4L, 10L);
  cells[3]     = entry (6L, 5L);
  cells[4]     = entry (2L, 10L);
  cells[5]     = entry (5L, 5L);
  cells[6]     = entry (4L, 3L);

  entry *to_place    = new entry[50];
  size_t to_place_sz = 43L;

  to_place[0]  = cells[0];
  to_place[5]  = cells[1];
  to_place[10] = cells[2];
  to_place[20] = cells[3];
  to_place[25] = cells[4];
  to_place[35] = cells[5];
  to_place[40] = cells[6];


  entry  replaced[50];
  size_t sz = 0;

  ordered_array o1;
  o1.add (to_place, to_place_sz, replaced, &sz);

  ASSERT_EQ (o1.counter, 3);
  ASSERT_EQ (o1.get_size (), 20);

  ASSERT_TRUE(o1.cells[0].val == 2);
  ASSERT_TRUE(o1.cells[0].count == 10);

  ASSERT_TRUE(o1.cells[1].val == 4);
  ASSERT_TRUE(o1.cells[1].count == 8);

  ASSERT_TRUE(o1.cells[2].val == 5);
  ASSERT_TRUE(o1.cells[2].count == 2);


  
  ASSERT_EQ (sz, 23);
  
  ASSERT_TRUE(replaced[0].val == 5);
  ASSERT_TRUE(replaced[0].count == 5);

  ASSERT_TRUE(replaced[5].val == 3);
  ASSERT_TRUE(replaced[5].count == 5);

  ASSERT_TRUE(replaced[10].val == 4);
  ASSERT_TRUE(replaced[10].count == 5);

  ASSERT_TRUE(replaced[15].val == 6);
  ASSERT_TRUE(replaced[15].count == 5);

  ASSERT_TRUE(replaced[20].val == 5);
  ASSERT_TRUE(replaced[20].count == 3);
}
