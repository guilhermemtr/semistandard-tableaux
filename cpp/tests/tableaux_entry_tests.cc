#include <gtest/gtest.h>

#include "semistandard_tableaux/tableaux_entry.hpp"

using namespace __placid::semistandard_tableaux;

TEST (semistandard_tableaux_entry, test_creation)
{
  entry e1;

  ASSERT_EQ (e1.val, 0);
  ASSERT_EQ (e1.count, 1);

  entry e2 (1);

  ASSERT_EQ (e2.val, 1);
  ASSERT_EQ (e2.count, 1);

  entry e3 (2, 2);

  ASSERT_EQ (e3.val, 2);
  ASSERT_EQ (e3.count, 2);

  entry e4 (e3);

  ASSERT_EQ (e4.val, e3.val);
  ASSERT_EQ (e4.count, e3.count);
}

TEST (semistandard_tableaux_entry, test_assignment)
{
  entry e1;

  e1 = 3;

  ASSERT_EQ (e1.val, 3);
  ASSERT_EQ (e1.count, 1);

  entry e2 = e1;

  ASSERT_EQ (e2.val, 3);
  ASSERT_EQ (e2.count, 1);
}

TEST (semistandard_tableaux_entry, test_equality)
{
  entry e1 (2, 3);
  entry e2 (e1);
  entry e3 (4, 2);

  ASSERT_TRUE (e1 == e2);
  ASSERT_TRUE (e1 != e3);
  ASSERT_TRUE (e2 != e3);
}
