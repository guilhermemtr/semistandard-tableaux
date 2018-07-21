#include <cstring>

#include "magma_element.hpp"
#include "ring_element.hpp"

using namespace __placid;

template <class T>
void
test_magma_element_file_read (magma_element<T> &fe, char *file)
{
  FILE *f = fmemopen (file, (1 + strlen (file)) * sizeof (char), "r");

  fe.read (f);

  fclose (f);
}

template <class T>
char *
test_magma_element_file_write (magma_element<T> &fe, size_t file_len)
{
  char *file = (char *) malloc (file_len * sizeof (char));
  FILE *f    = fmemopen (file, file_len * sizeof (char), "w");

  fe.write (f);

  fclose (f);

  return file;
}

void
initialize_square_matrix_2 (
  tropical_matrix &m, tn_t e1, tn_t e2, tn_t e3, tn_t e4)
{
  tropical_number tns[4] = {tropical_number (e1),
                            tropical_number (e2),
                            tropical_number (e3),
                            tropical_number (e4)};

  if (!((m.rows == m.columns) && (m.rows == 2)))
  {
    return;
  }

  for (size_t i = 0; i < m.rows * m.columns; i++)
  {
    m.matrix[i] = tns[i];
  }
}

void
initialize_square_matrix_3 (tropical_matrix &m,
                            tn_t             e1,
                            tn_t             e2,
                            tn_t             e3,
                            tn_t             e4,
                            tn_t             e5,
                            tn_t             e6,
                            tn_t             e7,
                            tn_t             e8,
                            tn_t             e9)
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

  if (!((m.rows == m.columns) && (m.rows == 3)))
  {
    return;
  }

  for (size_t i = 0; i < m.rows * m.columns; i++)
  {
    m.matrix[i] = tns[i];
  }
}
