#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"


#include "tuple.hpp"
#include "tropical_elements/tropical_matrix.hpp"
#include "free_monoid/knuth_homomorphism.hpp"

using namespace __placid::free_monoid;

TEST (knuth_homomorphism, test_knuth_relations_satisfied)
{
  char file_buffer[1 << 14];

  strcpy (
    file_buffer,
    "tuple\n5\ntropical_matrix\n1\n4 4\n0    -inf -inf -inf\n-inf 0    -inf "
    "-inf\n-inf -inf 0    -inf\n-inf -inf -inf 0\n\n,\ntropical_matrix\n1\n4 "
    "4\n1    1    1    1\n-inf 0    0    0\n-inf -inf 0    0\n-inf -inf -inf "
    "0\n\n,\ntropical_matrix\n1\n4 4\n0    1    1    1\n-inf 1    1    1\n-inf "
    "-inf 0    0\n-inf -inf -inf 0\n\n,\ntropical_matrix\n1\n4 4\n0    0    1  "
    "  "
    "1\n-inf 0    1    1\n-inf -inf 1    1\n-inf -inf -inf "
    "0\n\n,\ntropical_matrix\n1\n4 4\n0    0    0    1\n-inf 0    0    1\n-inf "
    "-inf 0    1\n-inf -inf -inf 1\n");

  tuple<tropical_elements::matrix> t;

  test_magma_element_file_read (t, file_buffer);

  knuth_homomorphism<tropical_elements::matrix> h(t);

  ASSERT_TRUE(h.knuth_relations_satisfied());
  
}

TEST (knuth_homomorphism, test_knuth_relations_unsatisfied)
{
  char file_buffer[1 << 14];

  strcpy (
    file_buffer,
    "tuple\n5\ntropical_matrix\n1\n4 4\n0    -inf -inf -inf\n-inf 0    -inf "
    "-inf\n-inf -inf 0    -inf\n-inf -inf -inf 0\n\n,\ntropical_matrix\n1\n4 "
    "4\n1    1    1    1\n-inf 0    0    0\n-inf -inf 0    0\n-inf -inf -inf "
    "0\n\n,\ntropical_matrix\n1\n4 4\n0    1    1    1\n-inf 1    1    1\n-inf "
    "-inf 0    0\n-inf -inf -inf 0\n\n,\ntropical_matrix\n1\n4 4\n0    0    1  "
    "  "
    "1\n-inf 0    1    1\n-inf -inf 1    1\n-inf -inf -inf "
    "0\n\n,\ntropical_matrix\n1\n4 4\n0    0    0    1\n-inf 0    0    1\n-inf "
    "-inf 0    1\n-inf -inf -inf 0\n"); //changed the last 1 to 0

  tuple<tropical_elements::matrix> t;

  test_magma_element_file_read (t, file_buffer);

  knuth_homomorphism<tropical_elements::matrix> h(t);

  ASSERT_FALSE(h.knuth_relations_satisfied());
  
}
