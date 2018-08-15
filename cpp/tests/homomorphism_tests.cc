#include <gtest/gtest.h>

#include "free_monoid/free_monoid_homomorphism.hpp"
#include "tropical_elements/tropical_number.hpp"

using namespace __placid::free_monoid;

TEST (free_monoid_homomorphism, test_default_creation)
{
  size_t alphabet_sz = 3;
  int    alphabet[alphabet_sz];
  for (size_t i = 0; i < alphabet_sz; i++)
  {
    alphabet[i] = i;
  }

  homomorphism<int> phi (alphabet, alphabet_sz - 1);

  ASSERT_TRUE (phi.length == alphabet_sz);
  for (size_t i = 0; i < alphabet_sz; i++)
  {
    ASSERT_TRUE (phi.mapping[i] == alphabet[i]);
  }
}

TEST (free_monoid_homomorphism, test_creation_from_homomorphism)
{
  size_t alphabet_sz = 3;
  int    alphabet[alphabet_sz];
  for (size_t i = 0; i < alphabet_sz; i++)
  {
    alphabet[i] = i;
  }

  homomorphism<int> phi1 (alphabet, alphabet_sz - 1);
  homomorphism<int> phi2 (phi1);

  ASSERT_TRUE (phi1.length == phi2.length);

  for (size_t i = 0; i < phi1.length; i++)
  {
    ASSERT_TRUE (phi1.mapping[i] == phi2.mapping[i]);
  }
}

TEST (free_monoid_homomorphism, test_max_rank)
{
  size_t alphabet_sz = 3;
  int    alphabet[alphabet_sz];
  for (size_t i = 0; i < alphabet_sz; i++)
  {
    alphabet[i] = i;
  }

  homomorphism<int> phi (alphabet, alphabet_sz - 1);

  ASSERT_TRUE (phi.max_rank () == alphabet_sz - 1);
}

TEST (free_monoid_homomorphism, test_map)
{
  size_t alphabet_sz = 4;
  symbol alphabet[alphabet_sz];
  for (size_t i = 0; i < alphabet_sz; i++)
  {
    alphabet[i] = i;
  }

  homomorphism<symbol> phi (alphabet, alphabet_sz - 1);

  element e0 (0);

  element e1 (&alphabet[1], 1);

  element e2 (e1);
  e2.add (&alphabet[2], 1);

  element e3 (e2);
  e3.add (&alphabet[3], 1);

  element e4 (e3);
  e4.add (&alphabet[2], 1);

  ASSERT_TRUE (phi.map (e0) == 0);

  ASSERT_TRUE (phi.map (e1) == 1);

  ASSERT_TRUE (phi.map (e2) == 2);

  ASSERT_TRUE (phi.map (e3) == 6);

  ASSERT_TRUE (phi.map (e4) == 12);
}
