#include <gtest/gtest.h>

#include "tropical_elements/tropical_number.hpp"
#include "magma_element_test_utils.hpp"

using namespace __placid;

TEST (tropical_number, test_creation)
{
  tn_t            n = 1000;
  tropical_number tn (n);
  ASSERT_EQ (n, tn.get ());
}

TEST (tropical_number, test_comparisons)
{
  tn_t n1 = 1000;
  tn_t n2 = 1001;

  tn_t i1 = tropical_number::get_infinite ().get ();
  tn_t i2 = i1 + n1;

  tropical_number tn1 (n1);
  tropical_number tn2 (n2);

  tropical_number ti1 (i1);
  tropical_number ti2 (i2);

  ASSERT_FALSE (tn1 == tn2 || tn1 == ti1 || tn2 == ti1 || tn2 == ti2);
  ASSERT_TRUE (tn1 != tn2 && tn1 != ti1 && tn2 != ti1 && tn2 != ti2);

  ASSERT_TRUE (ti1 == ti2);
  ASSERT_FALSE (ti1 != ti2);
}

TEST (tropical_number, test_infinity_check)
{
  tn_t n1 = 1000;
  tn_t n2 = 0;
  tn_t n3 = tropical_number::get_infinite ().get () - n1;

  tn_t i1 = tropical_number::get_infinite ().get ();
  tn_t i2 = i1 + n1;
  tn_t i3 = i2 + i1;


  tropical_number tn1 (n1);
  tropical_number tn2 (n2);
  tropical_number tn3 (n3);

  tropical_number ti1 (i1);
  tropical_number ti2 (i2);
  tropical_number ti3 (i3);


  ASSERT_TRUE (!tn1);
  ASSERT_TRUE (!tn2);
  ASSERT_TRUE (!tn3);

  ASSERT_FALSE (!ti1);
  ASSERT_FALSE (!ti2);
  ASSERT_FALSE (!ti3);
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

  tropical_number tn_res3 = ti1 + ti2;
  bool valid_outcome      = (tn_res3.get () == i1) || (tn_res3.get () == i2);
  ASSERT_TRUE (valid_outcome);
}

TEST (tropical_number, test_mult)
{
  tn_t n1 = 1000;
  tn_t n2 = 1001;

  tn_t i1 = tropical_number::get_infinite ().get ();
  tn_t i2 = tropical_number::get_infinite ().get () + n1;


  tropical_number tn1 (n1);
  tropical_number tn2 (n2);

  tropical_number ti1 (i1);
  tropical_number ti2 (i2);


  tropical_number tn_res1 = tn1 * tn2;
  ASSERT_EQ (tn_res1.get (), n1 + n2);
  ASSERT_TRUE (!tn_res1);

  tropical_number tn_res2 = tn1 * ti1;
  ASSERT_EQ (tn_res2.get (), n1 + i1);
  ASSERT_FALSE (!tn_res2);

  tropical_number tn_res3 = tn2 * ti1;
  ASSERT_EQ (tn_res3.get (), n2 + i1);
  ASSERT_FALSE (!tn_res3);

  tropical_number tn_res4 = ti1 * ti2;
  ASSERT_EQ (tn_res4.get (), i1 + i2);
  ASSERT_FALSE (!tn_res4);
}

TEST (tropical_number, test_read)
{
  const char *mode = "r";

  char *sn1 = (char *) "1230";
  char *sn2 = (char *) "1230L";
  char *si  = (char *) "-inf";

  tn_t n1 = atoll (sn1);
  tn_t i  = tropical_number::get_infinite ().get ();

  tropical_number tn1 (n1);
  tropical_number ti (i);

  tropical_number v = 0;

  test_magma_element_file_read (v, sn1);
  ASSERT_EQ (v.get (), tn1.get ());

  test_magma_element_file_read (v, sn2);
  ASSERT_EQ (v.get (), tn1.get ());

  test_magma_element_file_read (v, si);
  EXPECT_EQ (v.get (), ti.get ());
  ASSERT_TRUE (v == ti);
}


TEST (tropical_number, test_write)
{
  char *sn = (char *) "1230 ";
  char *si = (char *) "-inf ";

  tn_t n = 1230;
  tn_t i = tropical_number::get_infinite ().get ();

  tropical_number tn (n);
  tropical_number ti (i);

  size_t f1_len = (strlen (sn) + 2) * sizeof (char);
  size_t f2_len = (strlen (si) + 2) * sizeof (char);

  char *f1 = test_magma_element_file_write (tn, f1_len);
  char *f2 = test_magma_element_file_write (ti, f2_len);

  ASSERT_TRUE (strcmp (sn, f1) == 0);
  ASSERT_TRUE (strcmp (si, f2) == 0);
}
