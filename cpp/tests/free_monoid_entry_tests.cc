#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"
#include "free_monoid/free_monoid_entry.hpp"

using namespace __placid::free_monoid;

TEST (free_monoid_entry, test_creation)
{
  entry e1;

  ASSERT_EQ (e1.sym, 0);
  ASSERT_EQ (e1.count, 1);

  entry e2 (1);

  ASSERT_EQ (e2.sym, 1);
  ASSERT_EQ (e2.count, 1);

  entry e3 (2, 2);

  ASSERT_EQ (e3.sym, 2);
  ASSERT_EQ (e3.count, 2);

  entry e4 (e3);

  ASSERT_EQ (e4.sym, e3.sym);
  ASSERT_EQ (e4.count, e3.count);
}

TEST (free_monoid_entry, test_assignment)
{
  entry e1;

  e1 = 3;

  ASSERT_EQ (e1.sym, 3);
  ASSERT_EQ (e1.count, 1);

  entry e2 = e1;

  ASSERT_EQ (e2.sym, 3);
  ASSERT_EQ (e2.count, 1);
}

TEST (free_monoid_entry, test_equality)
{
  entry e1 (2, 3);
  entry e2 (e1);
  entry e3 (4, 2);

  ASSERT_TRUE (e1 == e2);
  ASSERT_TRUE (e1 != e3);
  ASSERT_TRUE (e2 != e3);
}
