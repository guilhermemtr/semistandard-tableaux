#include <gtest/gtest.h>

#include "magma_element_pool.hpp"
#include "tropical_elements/tropical_number.hpp"
#include "tropical_elements/tropical_matrix.hpp"

using namespace __placid;

TEST (magma_element_pool, test_default_creation)
{
  pool<tropical_elements::number> p1;

  ASSERT_TRUE (p1.size == pool<std::string>::default_size);
  ASSERT_TRUE (p1.counter == 0);

  pool<tropical_elements::number> p2 (17);

  ASSERT_TRUE (p2.size == 17);
  ASSERT_TRUE (p2.counter == 0);
}

TEST (magma_element_pool, test_get_size)
{
  pool<tropical_elements::number> p1;

  tropical_elements::number a;
  p1.elements[0] = a;
  p1.elements[1] = 3;
  p1.counter     = 2;

  ASSERT_TRUE (p1.get_size () == 2);
}


TEST (magma_element_pool, test_contains)
{
  pool<tropical_elements::number> p1;

  tropical_elements::number a;
  p1.elements[0] = a;
  p1.elements[1] = 3;
  p1.counter     = 2;

  ASSERT_TRUE (p1.contains (3));
  ASSERT_TRUE (p1.contains (-1));    // checks if the pool has -inf
  ASSERT_FALSE (p1.contains (2));
}

TEST (magma_element_pool, test_add)
{
  pool<tropical_elements::number> p1;

  tropical_elements::number a;

  ASSERT_FALSE (p1.contains (a));

  p1.add (a);

  ASSERT_TRUE (p1.contains (a));
}

TEST (magma_element_pool, test_creation_from_pool)
{
  pool<tropical_elements::number> p1;

  for (int i = -1; i < 10; i++)
  {
    p1.add (i);
  }

  for (int i = -1; i < 10; i++)
  {
    p1.add (i);
  }

  pool<tropical_elements::number> p2 (p1);

  ASSERT_TRUE (p1.size == p2.size);
  ASSERT_TRUE (p1.counter == p2.counter);
  for (size_t i = 0; i < p1.counter; i++)
  {
    EXPECT_TRUE (p1.elements[i] == p2.elements[i]);
    ASSERT_TRUE (p1.contains (p2.elements[i]));
    ASSERT_TRUE (p2.contains (p1.elements[i]));
  }
}

TEST (magma_element_pool, test_remove_duplicates)
{
  pool<tropical_elements::number> p1;

  tropical_elements::number a;
  p1.add (a);
  p1.add (a);

  p1.add (3);
  p1.add (4);
  p1.add (3);
  p1.add (5);

  ASSERT_TRUE (p1.get_size () == 6);

  p1.remove_duplicates ();

  ASSERT_TRUE (p1.get_size () == 4);

  ASSERT_TRUE (p1.contains (a));
  ASSERT_TRUE (p1.contains (3));
  ASSERT_TRUE (p1.contains (4));
  ASSERT_TRUE (p1.contains (5));
}

TEST (magma_element_pool, test_identity_testing)
{
  pool<tropical_elements::number> p1;

  for (int i = -1; i < 10; i++)
  {
    p1.add (i);
  }

  std::string id1 ("p = p");

  p1.test_identity (id1);

  std::string id2 ("p.q = p.q");

  p1.test_identity (id2);

  std::string id3 ("p.q = q.p");

  p1.test_identity (id3);

  std::string id4 ("p = q.p");

  try
  {
    p1.test_identity (id4);
    printf ("Exception was expected\n");
    ASSERT_TRUE (false);
  } catch (std::unordered_map<std::string, tropical_elements::number> e)
  {
    for (auto it : e)
    {
      // printf ("%s:\t", it.first.c_str ());
      // it.second.write (stdout);
      // printf ("\n");
    }
  }

  std::string id5 ("q.p.p.q = p.q.q.p");

  p1.test_identity (id5);
}
