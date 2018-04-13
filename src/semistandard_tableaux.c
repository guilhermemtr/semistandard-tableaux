#include "semistandard_tableaux.h"

#ifdef __SST_TABLEAUX__

static void
__sst_tableaux_initialize_rows (__sst_tableaux_t *_sst)
{
  for (size_t i = _sst->counter; i < _sst->size; i++)
  {
    __sst_ordered_array_create (&(_sst->columns[i]));
  }
}

__sst_tableaux_t *
__sst_tableaux_create (void)
{
  __sst_tableaux_t *tableaux = malloc (sizeof (__sst_tableaux_t));
  tableaux->size             = __SST_ORDERED_ARRAY_DEFAULT_SIZE;
  tableaux->counter          = 0;
  tableaux->columns = malloc (tableaux->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (tableaux);
  return tableaux;
}

static void
__sst_tableaux_resize (__sst_tableaux_t *_sst)
{
  _sst->size = (_sst->size + 1) << 1;    // multiplication by two
  _sst->columns =
    realloc (_sst->columns, _sst->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (_sst);
}

static void
__sst_tableaux_add_cell (__sst_tableaux_t *_sst, const __tableaux_cell_t cell)
{
  __sst_ordered_array_place_result_t res      = REPLACED;
  __tableaux_cell_t                  to_place = cell;
  __tableaux_cell_t                  replaced;
  size_t                             j = 0;
  while (res != APPENDED)
  {
    if (j == _sst->size)
    {
      __sst_tableaux_resize (_sst);
    }
    if (j == _sst->counter)
    {
      _sst->counter++;
    }
    res =
      __sst_ordered_array_place (&(_sst->columns[j++]), to_place, &replaced);
    to_place = replaced;
  }
}

void
__sst_tableaux_init (__sst_tableaux_t *       _sst,
                     const __tableaux_cell_t *_sst_values,
                     const size_t             sz)
{
  for (size_t i = 0; i < sz; i++)
  {
    __sst_tableaux_add_cell (_sst, _sst_values[i]);
  }
}

void
__sst_tableaux_destroy (__sst_tableaux_t *_sst)
{
  for (size_t i = 0; i < _sst->size; i++)
  {
    __sst_ordered_array_destroy (&(_sst->columns[i]));
  }
  free (_sst->columns);
  free (_sst);
}

void
__sst_tableaux_iterate_tableaux (const __sst_tableaux_t *_sst,
                                 iteration_function      fn,
                                 void *                  data)
{
  size_t index = 0;
  size_t i     = 0;
  size_t j     = _sst->counter;
  while (j != 0)
  {
    while (i < _sst->columns[j - 1].counter)
    {
      ptrdiff_t offset = fn (_sst->columns[j - 1].array[i++], index++, data);
      if (offset != 1)
      {
        abort ();    // not yet implemented
      }
    }
    i = 0;
    j--;
  }
}

size_t
__sst_tableaux_size (const __sst_tableaux_t *_sst)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->columns[i].counter; j++)
    {
      total_size += _sst->columns[i].array[j].length;
    }
  }
  return total_size;
}

size_t
__sst_tableaux_storage_size (const __sst_tableaux_t *_sst)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    total_size += _sst->columns[i].counter;
  }
  return total_size;
}

static ptrdiff_t
__sst_tableaux_read_iteration_function (__tableaux_cell_t cell,
                                        size_t            index,
                                        void *            data)
{
  __tableaux_cell_val_t *vector = (__tableaux_cell_val_t *) data;
  vector[index]                 = cell.val;
  return (ptrdiff_t) 1;
}

size_t
__sst_tableaux_read_tableaux (const __sst_tableaux_t *      _sst,
                              const __tableaux_cell_val_t **_sst_tableaux_cells)
{
  size_t total_size    = __sst_tableaux_size (_sst);
  *_sst_tableaux_cells = malloc (total_size * sizeof (__tableaux_cell_val_t));
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_read_iteration_function, _sst_tableaux_cells);
  return total_size;
}

static ptrdiff_t
__sst_tableaux_multiply_iteration_function (const __tableaux_cell_t cell,
                                            const size_t            index,
                                            void *                  data)
{
  __sst_tableaux_t *_sst_result = (__sst_tableaux_t *) data;
  __sst_tableaux_add_cell (_sst_result, cell);
  return (ptrdiff_t) 1;
}

static void
__sst_tableaux_resize_to (__sst_tableaux_t *_sst, const size_t sz)
{
  _sst->size = sz;
  _sst->columns =
    realloc (_sst->columns, _sst->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (_sst);
}

void
__sst_tableaux_multiply (const __sst_tableaux_t *_sst_left,
                         const __sst_tableaux_t *_sst_right,
                         __sst_tableaux_t *      _sst_result)
{
  _sst_result->counter = 0;
  if (__builtin_expect (_sst_left->counter >= _sst_result->size, 0))
  {
    __sst_tableaux_resize_to (_sst_result, _sst_left->counter);
  }

  for (size_t i = 0; i < _sst_left->counter; i++)
  {
    __sst_ordered_array_copy (&_sst_left->columns[i], &_sst_result->columns[i]);
  }

  __sst_tableaux_iterate_tableaux (
    _sst_right, __sst_tableaux_multiply_iteration_function, _sst_result);
}

bool
__sst_tableaux_check (const __sst_tableaux_t *_sst)
{
  bool ok = true;

  // first, check sizes
  if (_sst->counter == 0)
  {
    return ok;
  }

  size_t prev = _sst->columns[0].counter;
  for (size_t j = 0; j < _sst->counter; j++)
  {
    ok   = ok && prev >= _sst->columns[j].counter;
    prev = _sst->columns[j].counter;
    if (!ok)
    {
      return ok;
    }
  }

  // second, check value constraints
  for (size_t j = 0; j < _sst->counter; j++)
  {
    for (size_t i = 0; i < _sst->columns[j].counter; i++)
    {
      ok = ok
           && (i + 1 >= _sst->columns[j].counter
               || _sst->columns[j].array[i].val
                    <= _sst->columns[j].array[i + 1].val);
      ok = ok
           && (j + 1 >= _sst->counter
               || _sst->columns[j + 1].array[i].val
                    < _sst->columns[j + 1].array[i].val);

      if (!ok)
      {
        return ok;
      }
    }
  }
  return ok;
}

__sst_tableaux_t *
__sst_tableaux_read_file (const char *filename)
{
  FILE *            f    = fopen (filename, "r");
  __sst_tableaux_t *_sst = __sst_tableaux_create ();
  __tableaux_cell_t cell = {0, 0};
  while (fscanf (f, "%lu", &(cell.val)) != EOF)
  {
    __sst_tableaux_add_cell (_sst, cell);
  }
  return _sst;
}

__sst_tableaux_t *
__sst_tableaux_read_structured_file (const char *filename)
{
  FILE *            f    = fopen (filename, "r");
  __sst_tableaux_t *_sst = __sst_tableaux_create ();

  char * line = NULL;
  size_t len  = 0;
  char * token1;
  char * token2;
  char * save_ptr1;
  char * save_ptr2;
  char * end_ptr  = NULL;
  int    base_val = 10;
  int    base_tag = 16;

  while (getline (&line, &len, f) != -1)
  {
    token1 = strtok_r (line, ",", &save_ptr1);

    while (token1 != NULL)
    {
      token2                        = strtok_r (token1, ":", &save_ptr2);
      __tableaux_cell_val_t v       = strtoull (token2, &end_ptr, base_val);
      token2                        = strtok_r (NULL, ":", &save_ptr2);
      __tableaux_cell_length_t l    = strtoull (token2, &end_ptr, base_tag);
      __tableaux_cell_t        cell = {.val = v, .length = l};


      token1 = strtok_r (NULL, ",", &save_ptr1);
    }

    free (line);
    line = NULL;
    len  = 0;
  }

  __tableaux_cell_t cell;
  while (fscanf (f, "%lu", &(cell.val)) != EOF)
  {
    __sst_tableaux_add_cell (_sst, cell);
  }
  return _sst;
}

static ptrdiff_t
__sst_tableaux_write_file_iterator_function (__tableaux_cell_t cell,
                                             size_t            sz,
                                             void *            data)
{
  FILE *f = (FILE *) data;
  fprintf (f, "%lu\n", cell.val);
  return (ptrdiff_t) 1;
}

void
__sst_tableaux_write_file (const __sst_tableaux_t *_sst, const char *filename)
{
  FILE *f = fopen (filename, "w");
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_write_file_iterator_function, f);
  fclose (f);
}

#endif    // __SST_TABLEAUX__
