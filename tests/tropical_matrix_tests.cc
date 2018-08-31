#include <gtest/gtest.h>

#include "tropical_elements/tropical_matrix.hpp"
#include "magma_element_test_utils.hpp"

using namespace __placid::tropical_elements;

void
initialize_square_matrix_2 (matrix &m, tn_t e1, tn_t e2, tn_t e3, tn_t e4)
{
  number tns[4] = {number (e1), number (e2), number (e3), number (e4)};

  if (!((m.rows == m.columns) && (m.rows == 2)))
  {
    return;
  }

  for (size_t i = 0; i < m.rows * m.columns; i++)
  {
    m.matrix_entries[i] = tns[i];
  }
}

void
initialize_square_matrix_3 (matrix &m,
                            tn_t    e1,
                            tn_t    e2,
                            tn_t    e3,
                            tn_t    e4,
                            tn_t    e5,
                            tn_t    e6,
                            tn_t    e7,
                            tn_t    e8,
                            tn_t    e9)
{
  number tns[9] = {number (e1),
                   number (e2),
                   number (e3),
                   number (e4),
                   number (e5),
                   number (e6),
                   number (e7),
                   number (e8),
                   number (e9)};

  if (!((m.rows == m.columns) && (m.rows == 3)))
  {
    return;
  }

  for (size_t i = 0; i < m.rows * m.columns; i++)
  {
    m.matrix_entries[i] = tns[i];
  }
}

TEST (matrix, test_default_creation)
{
  number ti = number ();
  matrix tm (2, 2);
  ASSERT_TRUE (tm.matrix_entries[0] == ti);
  ASSERT_TRUE (tm.matrix_entries[1] == ti);
  ASSERT_TRUE (tm.matrix_entries[2] == ti);
  ASSERT_TRUE (tm.matrix_entries[3] == ti);
}

TEST (matrix, test_creation_with_values)
{
  matrix tm (2, 2);
  initialize_square_matrix_2 (tm, 1, 2, 3, 4);

  ASSERT_EQ (tm.matrix_entries[0].get (), 1);
  ASSERT_EQ (tm.matrix_entries[1].get (), 2);
  ASSERT_EQ (tm.matrix_entries[2].get (), 3);
  ASSERT_EQ (tm.matrix_entries[3].get (), 4);
}


TEST (matrix, test_comparisons)
{
  matrix tm1 (2, 2);
  matrix tm2 (2, 2);
  matrix tm3 (2, 2);

  initialize_square_matrix_2 (tm1, 1, 2, 3, 4);
  initialize_square_matrix_2 (tm2, 2, 3, 4, 5);
  initialize_square_matrix_2 (tm3, 1, 2, 3, 4);

  matrix tmi (2, 2);

  matrix tmi_12 (1, 2);
  matrix tmi_21 (2, 1);

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

TEST (matrix, test_sum)
{
  matrix tm1 (2, 2);
  matrix tm2 (2, 2);

  initialize_square_matrix_2 (tm1, 1, 2, 3, 4);
  initialize_square_matrix_2 (tm2, 2, 3, 4, 5);

  matrix tmi (2, 2);

  matrix tmi_12 (1, 2);
  matrix tmi_21 (2, 1);

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

TEST (matrix, test_mult)
{
  matrix tm1 (2, 2);
  matrix tm2 (2, 2);

  initialize_square_matrix_2 (tm1, 1, 2, 3, 4);
  initialize_square_matrix_2 (tm2, 2, 3, 4, 5);

  tn_t inf = number ().get ();

  matrix tm1_3 (3, 3);
  matrix tm2_3 (3, 3);
  matrix tm_res_3 (3, 3);

  initialize_square_matrix_3 (tm1_3, inf, 1, 2, 0, inf, 4, 0, 1, 1);
  initialize_square_matrix_3 (tm2_3, 0, 1, 1, inf, inf, 3, 0, 0, 0);
  initialize_square_matrix_3 (tm_res_3, 2, 2, 4, 4, 4, 4, 1, 1, 4);

  matrix tmi (2, 2);

  matrix tmi_11 (1, 1);
  matrix tmi_12 (1, 2);
  matrix tmi_21 (2, 1);

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

  matrix tm_res_11 (2, 2);
  matrix tm_res_12 (2, 2);
  matrix tm_res_21 (2, 2);
  matrix tm_res_22 (2, 2);

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

TEST (matrix, test_read_plain)
{
  char f1[1 << 10];
  char f2[1 << 10];
  char f3[1 << 10];

  strcpy (f1, "tropical_matrix\n0\n3 3\n 1 2 5 - - 2 - 3 -");
  strcpy (f2, "tropical_matrix\n0\n3 3\n - 1 2  0 - 4 0 1 1\n  ");
  strcpy (f3, "tropical_matrix\n0\n3 3\n0 1 1 - - 3 0L 0 0");

  matrix tm1 (3, 3);
  matrix tm2 (3, 3);
  matrix tm3 (3, 3);

  tn_t inf = number ().get ();

  matrix tm1_res (3, 3);
  matrix tm2_res (3, 3);
  matrix tm3_res (3, 3);

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

TEST (matrix, test_read_table)
{
  char f1[1 << 10];
  char f2[1 << 10];
  char f3[1 << 10];

  strcpy (f1, "tropical_matrix\n1\n3 3\n1 2 5\n - - 2\n - 3 -");
  strcpy (f2, "tropical_matrix\n1\n3 3\n - 1 2 \n 0 - 4\n 0 1 1\n  ");
  strcpy (f3, "tropical_matrix\n1\n3 3\n0 1 1\n - - 3\n 0L 0 0");

  matrix tm1 (3, 3);
  matrix tm2 (3, 3);
  matrix tm3 (3, 3);

  tn_t inf = number ().get ();

  matrix tm1_res (3, 3);
  matrix tm2_res (3, 3);
  matrix tm3_res (3, 3);

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


TEST (matrix, test_write_plain)
{
  file_format format = matrix::plain_format;
  tn_t        inf    = number ().get ();

  matrix tm1 (3, 3);
  matrix tm2 (3, 3);
  matrix tm3 (3, 3);

  initialize_square_matrix_3 (tm1, 1, 2, 5, inf, inf, 2, inf, 3, inf);
  initialize_square_matrix_3 (tm2, inf, 1, 2, 0, inf, 4, 0, 1, 1);
  initialize_square_matrix_3 (tm3, 0, 1, 1, inf, inf, 3, 0, 0, 0);

  char *f1 = test_magma_element_file_write (tm1, 1 << 10, format);
  char *f2 = test_magma_element_file_write (tm2, 1 << 10, format);
  char *f3 = test_magma_element_file_write (tm3, 1 << 10, format);

  ASSERT_TRUE (strcmp (f1,
                       "tropical_matrix\n0\n3 3\n1 \n2 \n5 \n- \n- \n2 "
                       "\n- \n3 \n- \n")
               == 0);
  ASSERT_TRUE (
    strcmp (f2, "tropical_matrix\n0\n3 3\n- \n1 \n2 \n0 \n- \n4 \n0 \n1 \n1 \n")
    == 0);
  ASSERT_TRUE (
    strcmp (f3, "tropical_matrix\n0\n3 3\n0 \n1 \n1 \n- \n- \n3 \n0 \n0 \n0 \n")
    == 0);

  free (f1);
  free (f2);
  free (f3);
}

TEST (matrix, test_write_table)
{
  file_format format = matrix::table_format;
  tn_t        inf    = number ().get ();

  matrix tm1 (3, 3);
  matrix tm2 (3, 3);
  matrix tm3 (3, 3);

  initialize_square_matrix_3 (tm1, 1, 2, 5, inf, inf, 2, inf, 3, inf);
  initialize_square_matrix_3 (tm2, inf, 1, 2, 0, inf, 4, 0, 1, 1);
  initialize_square_matrix_3 (tm3, 0, 1, 1, inf, inf, 3, 0, 0, 0);

  char *f1 = test_magma_element_file_write (tm1, 1 << 10, format);
  char *f2 = test_magma_element_file_write (tm2, 1 << 10, format);
  char *f3 = test_magma_element_file_write (tm3, 1 << 10, format);

  ASSERT_TRUE (
    strcmp (f1, "tropical_matrix\n1\n3 3\n1 2 5 \n- - 2 \n- 3 - \n") == 0);
  ASSERT_TRUE (strcmp (f2, "tropical_matrix\n1\n3 3\n- 1 2 \n0 - 4 \n0 1 1 \n")
               == 0);
  ASSERT_TRUE (strcmp (f3, "tropical_matrix\n1\n3 3\n0 1 1 \n- - 3 \n0 0 0 \n")
               == 0);

  free (f1);
  free (f2);
  free (f3);
}
