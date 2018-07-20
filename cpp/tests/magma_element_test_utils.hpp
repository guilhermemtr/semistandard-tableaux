#include <cstring>

#include "magma_element.hpp"
#include "ring_element.hpp"

using namespace __placid;

/*template <class T>
void
test_magma_element_file_read (magma_element<T> &fe, char *file);

template <class T>
char *
test_magma_element_file_write (magma_element<T> &fe, size_t file_len);*/

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

