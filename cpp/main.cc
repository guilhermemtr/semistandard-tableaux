#include <gtest/gtest.h>

#include <iostream>

#include "tropical_elements/tropical_number.hpp"

int
main (int argc, char **argv)
{
  __placid::tropical_number n (4);
  testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
