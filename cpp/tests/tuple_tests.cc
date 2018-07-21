#include <gtest/gtest.h>

#include "tuple.hpp"
#include "magma_element_test_utils.hpp"
#include "tropical_elements/tropical_number.hpp"

using namespace __placid;

TEST (tuple, test_creation)
{
  tropical_number        e1 (1);
  tropical_number        e2 (2);
  tropical_number        elems[2] = {e1, e2};
  tuple<tropical_number> tup (2, elems);

  ASSERT_TRUE (tup.arity == 2);
  ASSERT_TRUE (tup.elements[0] == e1);
  ASSERT_TRUE (tup.elements[1] == e2);
}

TEST (tuple, test_comparisons)
{
  tropical_number e1 (1);
  tropical_number e2 (2);
  tropical_number e3 (3);
  tropical_number e4 (4);

  tropical_number elems2_1[2] = {e1, e2};
  tropical_number elems2_2[2] = {e2, e3};
  tropical_number elems2_3[2] = {e3, e4};
  tropical_number elems3_1[3] = {e1, e2, e3};

  tuple<tropical_number> tup2_1 (2, elems2_1);
  tuple<tropical_number> tup2_2 (2, elems2_2);
  tuple<tropical_number> tup2_3 (2, elems2_3);
  tuple<tropical_number> tup3_1 (3, elems3_1);
  tuple<tropical_number> tup3_2 (3, elems3_1);

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
  tropical_number e0;
  tropical_number e1 (1);
  tropical_number e2 (2);
  tropical_number e3 (3);
  tropical_number e4 (4);
  

  tropical_number elems2_1[2] = {e0, e1};
  tropical_number elems2_2[2] = {e1, e2};
  tropical_number elems2_3[2] = {e2, e3};
  tropical_number elems3_1[3] = {e1, e2, e3};

  tuple<tropical_number> tup2_1 (2, elems2_1);
  tuple<tropical_number> tup2_2 (2, elems2_2);
  tuple<tropical_number> tup2_3 (2, elems2_3);
  tuple<tropical_number> tup3_1 (3, elems3_1);
  tuple<tropical_number> tup3_2 (3, elems3_1);

  // NOT OK:
  // tup2_1 tup3_1
  // tuples of different types

  
  // tup2_1 * tup2_1
  // 


  
  tuple tmi (2, 2);

  tuple tmi_11 (1, 1);
  tuple tmi_12 (1, 2);
  tuple tmi_21 (2, 1);

  try
  {
    tm1 *tmi_12;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tmi_21 *tm1;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tm1 *tmi_11;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tmi_12 *tmi_11;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tmi_11 *tmi_21;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tmi_12 *tmi_12;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tmi_21 *tmi_21;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  ASSERT_TRUE (tmi * tmi == tmi);
  ASSERT_TRUE (tm1 * tmi == tmi);
  ASSERT_TRUE (tm2 * tmi == tmi);
  ASSERT_TRUE (tmi * tm1 == tmi);
  ASSERT_TRUE (tmi * tm2 == tmi);
  ASSERT_TRUE (tmi_21 * tmi_12 == tmi);

  ASSERT_TRUE (tmi_12 * tmi_21 == tmi_11);
  ASSERT_TRUE (tmi_11 * tmi_11 == tmi_11);

  ASSERT_TRUE (tmi_21 * tmi_11 == tmi_21);
  ASSERT_TRUE (tmi_11 * tmi_12 == tmi_12);

  tuple tm_res_11 (2, 2);
  tuple tm_res_12 (2, 2);
  tuple tm_res_21 (2, 2);
  tuple tm_res_22 (2, 2);

  initialize_square_matrix_2 (tm_res_11, 5, 6, 7, 8);
  initialize_square_matrix_2 (tm_res_12, 6, 7, 8, 9);
  initialize_square_matrix_2 (tm_res_21, 6, 7, 8, 9);
  initialize_square_matrix_2 (tm_res_22, 7, 8, 9, 10);

  ASSERT_TRUE (tm1 * tm1 == tm_res_11);
  ASSERT_TRUE (tm1 * tm2 == tm_res_12);
  ASSERT_TRUE (tm2 * tm1 == tm_res_21);
  ASSERT_TRUE (tm2 * tm2 == tm_res_22);

  ASSERT_TRUE (tm1_3 * tm2_3 == tm_res_3);
}

/*TEST (tuple, test_read)
{
  char f1[1 << 10];
  char f2[1 << 10];
  char f3[1 << 10];

  strcpy (f1, "1 2 5\n -inf -inf 2\n -inf 3 -inf");
  strcpy (f2, "-inf 1 2 \n 0 -inf 4\n 0 1 1\n  ");
  strcpy (f3, "0 1 1\n -inf -inf 3\n 0L 0 0");

  tuple tm1 (3, 3);
  tuple tm2 (3, 3);
  tuple tm3 (3, 3);

  tn_t inf = tropical_number ().get ();

  tuple tm1_res (3, 3);
  tuple tm2_res (3, 3);
  tuple tm3_res (3, 3);

  initialize_square_matrix_3 (tm1_res, 1, 2, 5, inf, inf, 2, inf, 3, inf);
  initialize_square_matrix_3 (tm2_res, inf, 1, 2, 0, inf, 4, 0, 1, 1);
  initialize_square_matrix_3 (tm3_res, 0, 1, 1, inf, inf, 3, 0, 0, 0);

  test_magma_element_file_read (tm1, f1);
  test_magma_element_file_read (tm2, f2);
  test_magma_element_file_read (tm3, f3);

  ASSERT_TRUE (tm1 == tm1_res);
  ASSERT_TRUE (tm2 == tm2_res);
  ASSERT_TRUE (tm3 == tm3_res);
}


TEST (tuple, test_write)
{
  tn_t inf = tropical_number ().get ();

  tuple tm1 (3, 3);
  tuple tm2 (3, 3);
  tuple tm3 (3, 3);

  initialize_square_matrix_3 (tm1, 1, 2, 5, inf, inf, 2, inf, 3, inf);
  initialize_square_matrix_3 (tm2, inf, 1, 2, 0, inf, 4, 0, 1, 1);
  initialize_square_matrix_3 (tm3, 0, 1, 1, inf, inf, 3, 0, 0, 0);

  char *f1 = test_magma_element_file_write (tm1, 1 << 10);
  char *f2 = test_magma_element_file_write (tm2, 1 << 10);
  char *f3 = test_magma_element_file_write (tm3, 1 << 10);

  ASSERT_TRUE (strcmp (f1, "1 2 5 \n-inf -inf 2 \n-inf 3 -inf \n") == 0);
  ASSERT_TRUE (strcmp (f2, "-inf 1 2 \n0 -inf 4 \n0 1 1 \n") == 0);
  ASSERT_TRUE (strcmp (f3, "0 1 1 \n-inf -inf 3 \n0 0 0 \n") == 0);

  free (f1);
  free (f2);
  free (f3);
}
*/
