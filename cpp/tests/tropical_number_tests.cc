#include <gtest/gtest.h>

#include "tropical_elements/tropical_number.hpp"

using namespace __placid;

TEST (tropical_number, test_creation)
{
  tn_t            n = 1000;
  tropical_number tn (n);
  ASSERT_EQ (n, tn.get ());
}

TEST (tropical_number, test_sum)
{
  tn_t n1 = 1000;
  tn_t n2 = 1001;

  tn_t i1 = tropical_number::get_infinite ().get ();
  tn_t i2 = tropical_number::get_infinite ().get () + n1;

  tropical_number tn1 (n1);
  tropical_number tn2 (n2);

  tropical_number ti1 (i1);
  tropical_number ti2 (i2);

  tropical_number tn_res1 = tn1 + tn2;
  ASSERT_EQ (tn_res1.get (), n2);

  tropical_number tn_res2 = tn1 + ti1;
  ASSERT_EQ (tn_res2.get (), n1);

  tropical_number tn_res3 = i1 + i2;
  bool valid_outcome      = (tn_res3.get () == i1) || (tn_res3.get () == i2);
  printf ("%lu\n", ti1.get ());
  printf ("%lu\n", ti2.get ());
  
  printf ("%lu\n", tn_res3.get ());
  ASSERT_TRUE (valid_outcome);
}

/*res1 = __tn_mult (n1, n2);
res1 = __tn_sum (n2, i1);
res1 = __tn_mult (n2, i1);
res1 = __tn_sum (i1, i2);
res1 = __tn_mult (i1, i2);*/
