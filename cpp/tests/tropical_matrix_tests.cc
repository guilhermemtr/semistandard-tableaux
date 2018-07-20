#include <gtest/gtest.h>

#include "tropical_elements/tropical_matrix.hpp"
#include "magma_element_test_utils.hpp"

using namespace __placid;

tropical_matrix
create_square_matrix_2 (tn_t e1, tn_t e2, tn_t e3, tn_t e4)
{
  tropical_number tns[4] = {tropical_number (e1),
                            tropical_number (e2),
                            tropical_number (e3),
                            tropical_number (e4)};
  return tropical_matrix (2, 2, tns);
}

tropical_matrix
create_square_matrix_3 (tn_t e1,
                        tn_t e2,
                        tn_t e3,
                        tn_t e4,
                        tn_t e5,
                        tn_t e6,
                        tn_t e7,
                        tn_t e8,
                        tn_t e9)
{
  tropical_number tns[9] = {tropical_number (e1),
                            tropical_number (e2),
                            tropical_number (e3),
                            tropical_number (e4),
                            tropical_number (e5),
                            tropical_number (e6),
                            tropical_number (e7),
                            tropical_number (e8),
                            tropical_number (e9)};
  return tropical_matrix (3, 3, tns);
}

TEST (tropical_matrix, test_default_creation)
{
  tropical_number ti = tropical_number ();
  tropical_matrix tm (2, 2);
  ASSERT_TRUE (tm.matrix[0] == ti);
  ASSERT_TRUE (tm.matrix[1] == ti);
  ASSERT_TRUE (tm.matrix[2] == ti);
  ASSERT_TRUE (tm.matrix[3] == ti);
}

TEST (tropical_matrix, test_creation_with_values)
{
  tropical_matrix tm = create_square_matrix_2 (1, 2, 3, 4);
  ASSERT_EQ (tm.matrix[0].get (), 1);
  ASSERT_EQ (tm.matrix[1].get (), 2);
  ASSERT_EQ (tm.matrix[2].get (), 3);
  ASSERT_EQ (tm.matrix[3].get (), 4);
}


TEST (tropical_matrix, test_comparisons)
{
  tropical_matrix tm1 = create_square_matrix_2 (1, 2, 3, 4);
  tropical_matrix tm2 = create_square_matrix_2 (2, 3, 4, 5);
  tropical_matrix tm3 = create_square_matrix_2 (1, 2, 3, 4);

  tropical_matrix tmi (2, 2);

  tropical_matrix tmi_12 (1, 2);
  tropical_matrix tmi_21 (2, 1);

  ASSERT_FALSE (tm1 == tm2);
  ASSERT_TRUE (tm1 != tm2);

  ASSERT_FALSE (tm1 != tm3);
  ASSERT_TRUE (tm1 == tm3);

  ASSERT_FALSE (tm2 == tm3);
  ASSERT_TRUE (tm2 != tm3);

  ASSERT_FALSE (tm1 == tmi);
  ASSERT_TRUE (tm1 != tmi);

  ASSERT_FALSE (tm2 == tmi);
  ASSERT_TRUE (tm2 != tmi);

  ASSERT_FALSE (tmi_12 == tmi);
  ASSERT_TRUE (tmi_12 != tmi);

  ASSERT_FALSE (tmi_21 == tmi);
  ASSERT_TRUE (tmi_21 != tmi);

  ASSERT_FALSE (tmi_12 == tmi_21);
  ASSERT_TRUE (tmi_12 != tmi_21);
}

TEST (tropical_matrix, test_sum)
{
  tropical_matrix tm1 = create_square_matrix_2 (1, 2, 3, 4);
  tropical_matrix tm2 = create_square_matrix_2 (2, 3, 4, 5);

  tropical_matrix tmi (2, 2);

  tropical_matrix tmi_12 (1, 2);
  tropical_matrix tmi_21 (2, 1);

  try
  {
    tm1 + tmi_12;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tm1 + tmi_21;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  try
  {
    tmi_12 + tmi_21;
    ASSERT_TRUE (false);
  } catch (const std::string &e)
  {
    ASSERT_TRUE (e == invalid_matrix_sizes_exception);
  }

  ASSERT_TRUE (tm1 + tm2 == tm2);
  ASSERT_TRUE (tmi + tmi == tmi);
  ASSERT_TRUE (tm1 + tmi == tm1);
  ASSERT_TRUE (tm2 + tmi == tm2);
}

TEST (tropical_matrix, test_mult)
{
  tropical_matrix tm1 = create_square_matrix_2 (1, 2, 3, 4);
  tropical_matrix tm2 = create_square_matrix_2 (2, 3, 4, 5);

  tn_t inf = tropical_number ().get ();

  tropical_matrix tm1_3 =
    create_square_matrix_3 (inf, 1, 2, 0, inf, 4, 0, 1, 1);
  tropical_matrix tm2_3 =
    create_square_matrix_3 (0, 1, 1, inf, inf, 3, 0, 0, 0);

  tropical_matrix tm_res_3 = create_square_matrix_3 (2, 2, 4, 4, 4, 4, 1, 1, 4);

  tropical_matrix tmi (2, 2);

  tropical_matrix tmi_11 (1, 1);
  tropical_matrix tmi_12 (1, 2);
  tropical_matrix tmi_21 (2, 1);

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

  tropical_matrix tm_res_11 = create_square_matrix_2 (5, 6, 7, 8);
  tropical_matrix tm_res_12 = create_square_matrix_2 (6, 7, 8, 9);
  tropical_matrix tm_res_21 = create_square_matrix_2 (6, 7, 8, 9);
  tropical_matrix tm_res_22 = create_square_matrix_2 (7, 8, 9, 10);

  ASSERT_TRUE (tm1 * tm1 == tm_res_11);
  ASSERT_TRUE (tm1 * tm2 == tm_res_12);
  ASSERT_TRUE (tm2 * tm1 == tm_res_21);
  ASSERT_TRUE (tm2 * tm2 == tm_res_22);

  ASSERT_TRUE (tm1_3 * tm2_3 == tm_res_3);
}

TEST (tropical_matrix, test_read)
{
  const char *mode = "r";

  char *sn1 = (char *) "1230";
  char *sn2 = (char *) "1230L";
  char *si  = (char *) "-inf";

  tn_t n1 = atoll (sn1);
  tn_t i  = tropical_number ().get ();

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


TEST (tropical_matrix, test_write)
{
  char *sn = (char *) "1230 ";
  char *si = (char *) "-inf ";

  tn_t n = 1230;
  tn_t i = tropical_number ().get ();

  tropical_number tn (n);
  tropical_number ti (i);

  size_t f1_len = (strlen (sn) + 2) * sizeof (char);
  size_t f2_len = (strlen (si) + 2) * sizeof (char);

  char *f1 = test_magma_element_file_write (tn, f1_len);
  char *f2 = test_magma_element_file_write (ti, f2_len);

  ASSERT_TRUE (strcmp (sn, f1) == 0);
  ASSERT_TRUE (strcmp (si, f2) == 0);
}
