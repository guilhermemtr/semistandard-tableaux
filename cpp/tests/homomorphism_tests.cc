#include <gtest/gtest.h>

#include "free_monoid/free_monoid_homomorphism.hpp"
#include "tropical_elements/tropical_number.hpp"

using namespace __placid::free_monoid;

TEST (free_monoid_homomorphism, test_creation)
{
  homomorphism<int> phi (NULL,0);
  ASSERT_TRUE(true);
}
