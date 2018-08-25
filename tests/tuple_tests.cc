#include <gtest/gtest.h>

#include "tuple.hpp"
#include "magma_element_test_utils.hpp"
#include "tropical_elements/tropical_number.hpp"

using namespace __placid;

TEST (tuple, test_creation)
{
  tropical_elements::number        e1 (1);
  tropical_elements::number        e2 (2);
  tropical_elements::number        elems[2] = {e1, e2};
  tuple<tropical_elements::number> tup (2, elems);

  ASSERT_TRUE (tup.arity == 2);
  ASSERT_TRUE (tup.elements[0] == e1);
  ASSERT_TRUE (tup.elements[1] == e2);
}

TEST (tuple, test_comparisons)
{
  tropical_elements::number e1 (1);
  tropical_elements::number e2 (2);
  tropical_elements::number e3 (3);
  tropical_elements::number e4 (4);

  tropical_elements::number elems2_1[2] = {e1, e2};
  tropical_elements::number elems2_2[2] = {e2, e3};
  tropical_elements::number elems2_3[2] = {e3, e4};
  tropical_elements::number elems3_1[3] = {e1, e2, e3};

  tuple<tropical_elements::number> tup2_1 (2, elems2_1);
  tuple<tropical_elements::number> tup2_2 (2, elems2_2);
  tuple<tropical_elements::number> tup2_3 (2, elems2_3);
  tuple<tropical_elements::number> tup3_1 (3, elems3_1);
  tuple<tropical_elements::number> tup3_2 (3, elems3_1);

  ASSERT_FALSE (tup2_1 == tup2_2);
  ASSERT_TRUE (tup2_1 != tup2_2);

  ASSERT_FALSE (tup2_1 == tup2_3);
  ASSERT_TRUE (tup2_1 != tup2_3);

  ASSERT_FALSE (tup2_2 == tup2_3);
  ASSERT_TRUE (tup2_2 != tup2_3);

  ASSERT_FALSE (tup3_1 == tup2_1);
  ASSERT_TRUE (tup3_1 != tup2_1);

  ASSERT_FALSE (tup3_1 != tup3_2);
  ASSERT_TRUE (tup3_1 == tup3_2);
}

TEST (tuple, test_mult)
{
  tropical_elements::number e0;
  tropical_elements::number e1 (1);
  tropical_elements::number e2 (2);
  tropical_elements::number e3 (3);
  tropical_elements::number e4 (4);
  tropical_elements::number e6 (6);

  // setup of the pairs
  tropical_elements::number elems2_1[2] = {e0, e1};
  tropical_elements::number elems2_2[2] = {e1, e2};

  tuple<tropical_elements::number> tup2_1 (2, elems2_1);
  tuple<tropical_elements::number> tup2_2 (2, elems2_2);

  // setup of the triples
  tropical_elements::number elems3_1[3] = {e1, e2, e3};
  tropical_elements::number elems3_2[3] = {e2, e1, e0};

  tuple<tropical_elements::number> tup3_1 (3, elems3_1);
  tuple<tropical_elements::number> tup3_2 (3, elems3_2);


  tropical_elements::number elems2_res_11[2] = {e0, e2};
  tropical_elements::number elems2_res_21[2] = {e0, e3};
  tropical_elements::number elems2_res_22[2] = {e2, e4};

  tuple<tropical_elements::number> tup2_res_11 (2, elems2_res_11);
  tuple<tropical_elements::number> tup2_res_21 (2, elems2_res_21);
  tuple<tropical_elements::number> tup2_res_22 (2, elems2_res_22);

  tropical_elements::number elems3_res_11[3] = {e2, e4, e6};
  tropical_elements::number elems3_res_12[3] = {e3, e3, e0};
  tropical_elements::number elems3_res_22[3] = {e4, e2, e0};

  tuple<tropical_elements::number> tup3_res_11 (3, elems3_res_11);
  tuple<tropical_elements::number> tup3_res_12 (3, elems3_res_12);
  tuple<tropical_elements::number> tup3_res_22 (3, elems3_res_22);

  ASSERT_TRUE (tup2_1 * tup2_1 == tup2_res_11);
  ASSERT_TRUE (tup2_2 * tup2_1 == tup2_res_21);
  ASSERT_TRUE (tup2_2 * tup2_2 == tup2_res_22);

  ASSERT_TRUE (tup3_1 * tup3_1 == tup3_res_11);
  ASSERT_TRUE (tup3_1 * tup3_2 == tup3_res_12);
  ASSERT_TRUE (tup3_2 * tup3_2 == tup3_res_22);

  try
  {
    tup2_1 *tup3_1;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == incompatible_tuple_arities_exception);
  }

  try
  {
    tup3_1 *tup2_1;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == incompatible_tuple_arities_exception);
  }
}

TEST (tuple, test_read_numbers)
{
  tropical_elements::number e0;
  tropical_elements::number e1 (1);
  tropical_elements::number e2 (2);
  tropical_elements::number e3 (3);
  tropical_elements::number e4 (4);
  tropical_elements::number e5 (5);
  tropical_elements::number e6 (6);
  tropical_elements::number e7 (7);
  tropical_elements::number e8 (8);
  tropical_elements::number e9 (9);

  tropical_elements::number tns_1[2]  = {e1, e2};
  tropical_elements::number tns_2[5]  = {e0, e1, e2, e3, e4};
  tropical_elements::number tns_3[10] = {e0, e1, e2, e3, e4, e5, e6, e7, e8, e9};

  char f1[1 << 10];
  char f2[1 << 10];
  char f3[1 << 10];

  strcpy (f1, "tuple\n2\n1 \n,\n2 ");
  strcpy (f2, "tuple\n5\n-inf \n,\n1 \n,\n2 \n,\n3 \n,\n4 ");
  strcpy (f3,
          "tuple\n10\n-inf \n,\n1 \n,\n2 \n,\n3 \n,\n4 \n,\n5 \n,\n6 \n,\n7 "
          "\n,\n8 \n,\n9 ");

  tuple<tropical_elements::number> tup1 (2, tns_1);
  tuple<tropical_elements::number> tup2 (5, tns_2);
  tuple<tropical_elements::number> tup3 (10, tns_3);

  tuple<tropical_elements::number> tup1_res (2, tns_1);
  tuple<tropical_elements::number> tup2_res (5, tns_2);
  tuple<tropical_elements::number> tup3_res (10, tns_3);

  test_magma_element_file_read (tup1, f1);
  test_magma_element_file_read (tup2, f2);
  test_magma_element_file_read (tup3, f3);

  ASSERT_TRUE (tup1 == tup1_res);
  ASSERT_TRUE (tup2 == tup2_res);
  ASSERT_TRUE (tup3 == tup3_res);
}


TEST (tuple, test_write_numbers)
{
  tropical_elements::number e0;
  tropical_elements::number e1 (1);
  tropical_elements::number e2 (2);
  tropical_elements::number e3 (3);
  tropical_elements::number e4 (4);
  tropical_elements::number e5 (5);
  tropical_elements::number e6 (6);
  tropical_elements::number e7 (7);
  tropical_elements::number e8 (8);
  tropical_elements::number e9 (9);

  tropical_elements::number tns_1[2]  = {e1, e2};
  tropical_elements::number tns_2[5]  = {e0, e1, e2, e3, e4};
  tropical_elements::number tns_3[10] = {e0, e1, e2, e3, e4, e5, e6, e7, e8, e9};

  tuple<tropical_elements::number> tup1 (2, tns_1);
  tuple<tropical_elements::number> tup2 (5, tns_2);
  tuple<tropical_elements::number> tup3 (10, tns_3);

  char *tup1_res = test_magma_element_file_write (tup1, 1 << 10, 0);
  char *tup2_res = test_magma_element_file_write (tup2, 1 << 10, 0);
  char *tup3_res = test_magma_element_file_write (tup3, 1 << 10, 0);


  ASSERT_TRUE (strcmp (tup1_res, "tuple\n2\n1 \n,\n2 ") == 0);
  ASSERT_TRUE (strcmp (tup2_res, "tuple\n5\n-inf \n,\n1 \n,\n2 \n,\n3 \n,\n4 ")
               == 0);
  ASSERT_TRUE (strcmp (tup3_res,
                       "tuple\n10\n-inf \n,\n1 \n,\n2 \n,\n3 \n,\n4 \n,\n5 "
                       "\n,\n6 \n,\n7 \n,\n8 \n,\n9 ")
               == 0);
}
