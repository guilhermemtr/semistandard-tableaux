#include "semistandard_tableaux.h"

#ifdef __SST_TABLEAUX__

static void
__sst_tableaux_initialize_rows (__sst_tableaux_t *_sst)
{
  for (size_t i = _sst->counter; i < _sst->size; i++)
  {
    __sst_ordered_array_create (&(_sst->rows[i]));
  }
}

__sst_tableaux_t *
__sst_tableaux_create (void)
{
  __sst_tableaux_t *tableaux = malloc (sizeof (__sst_tableaux_t));
  tableaux->size             = __SST_ORDERED_ARRAY_DEFAULT_SIZE;
  tableaux->counter          = 0;
  tableaux->rows = malloc (tableaux->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (tableaux);
  return tableaux;
}

static void
__sst_tableaux_resize (__sst_tableaux_t *_sst)
{
  _sst->size = (_sst->size + 1) << 1;    // multiplication by two
  _sst->rows =
    realloc (_sst->rows, _sst->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (_sst);
}

static size_t
__sst_tableaux_add_cells (__sst_tableaux_t * _sst,
                          __tableaux_cell_t *cells,
                          size_t             real_nr_cells)
{
  __tableaux_cell_t arr1[real_nr_cells];
  __tableaux_cell_t arr2[real_nr_cells];

  __tableaux_cell_t *to_place = arr1;
  __tableaux_cell_t *replaced = arr2;

  size_t result_sz = 0;



  for (size_t i = 0, j = 0; j < real_nr_cells; j += cells[i++].len)
  {
    to_place[j] = cells[i];
  }

  size_t j = 0;

  while (real_nr_cells != 0)
  {
    if (j == _sst->counter)
    {
      if (_sst->counter == _sst->size)
      {
        __sst_tableaux_resize (_sst);
      }
      _sst->counter++;
    }

    __sst_ordered_array_place (
      &(_sst->rows[j]), to_place, real_nr_cells, replaced, &real_nr_cells);

    result_sz += _sst->rows[j++].counter;

    __tableaux_cell_t *tmp = to_place;
    to_place               = replaced;
    replaced               = tmp;
  }
  return result_sz;
}

void
__sst_tableaux_init (__sst_tableaux_t * _sst,
                     __tableaux_cell_t *_sst_values,
                     const size_t       sz)
{
  size_t real_sz = 0;
  for (size_t i = 0; i < sz; i++)
  {
    real_sz += _sst_values[i].len;
  }
  __sst_tableaux_add_cells (_sst, _sst_values, real_sz);
}

void
__sst_tableaux_destroy (__sst_tableaux_t *_sst)
{
  for (size_t i = 0; i < _sst->size; i++)
  {
    __sst_ordered_array_destroy (&(_sst->rows[i]));
  }
  free (_sst->rows);
  free (_sst);
}

size_t
__sst_tableaux_iterate_tableaux (const __sst_tableaux_t *_sst,
                                 iteration_function      fn,
                                 void *                  data)
{
  size_t index      = 0;
  size_t real_index = 0;
  size_t i          = 0;
  size_t j          = _sst->counter;
  while (j != 0)
  {
    while (i < _sst->rows[j - 1].counter)
    {
      ptrdiff_t offset =
        fn (_sst->rows[j - 1].array[i], index++, real_index, data);
      real_index += _sst->rows[j - 1].array[i++].len;

      if (offset != 1)
      {
        abort ();    // not yet implemented
      }
    }
    i = 0;
    j--;
  }
  return real_index;
}

size_t
__sst_tableaux_size (const __sst_tableaux_t *_sst)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      total_size += _sst->rows[i].array[j].len;
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
    total_size += _sst->rows[i].counter;
  }
  return total_size;
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

  size_t prev = _sst->rows[0].counter;
  for (size_t j = 0; j < _sst->counter; j++)
  {
    ok   = ok && prev >= __sst_ordered_array_real_length (&(_sst->rows[j]));
    prev = __sst_ordered_array_real_length (&(_sst->rows[j]));
    if (!ok)
    {
      return ok;    // haha
    }
  }

  // second, check value constraints
  for (size_t j = 0; j < _sst->counter; j++)
  {
    for (size_t i = 0; i < _sst->rows[j].counter; i++)
    {
      ok = ok
           && (i + 1 >= _sst->rows[j].counter
               || _sst->rows[j].array[i].val < _sst->rows[j].array[i + 1].val);
      ok =
        ok
        && (j + 1 >= _sst->counter
            || _sst->rows[j + 1].array[i].val < _sst->rows[j + 1].array[i].val);

      if (!ok)
      {
        return ok;
      }
    }
  }
  return ok;
}

static void
__sst_tableaux_resize_to (__sst_tableaux_t *_sst, const size_t sz)
{
  _sst->size = sz;
  _sst->rows =
    realloc (_sst->rows, _sst->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (_sst);
}

size_t
__sst_tableaux_fast_multiply (const __sst_tableaux_t *_sst_left,
                              const __sst_tableaux_t *_sst_right,
                              const size_t            sz_right,
                              __sst_tableaux_t *      _sst_result)
{
  _sst_result->counter = 0;
  if (__builtin_expect (_sst_left->counter >= _sst_result->size, 0))
  {
    __sst_tableaux_resize_to (_sst_result, _sst_left->counter);
  }

  for (size_t i = 0; i < _sst_left->counter; i++)
  {
    __sst_ordered_array_copy (&_sst_left->rows[i], &_sst_result->rows[i]);
  }

  __tableaux_cell_t right_tableaux[sz_right];
  size_t            real_sz_right =
    __sst_tableaux_read_to_compressed_tableaux (_sst_right, right_tableaux);

  return __sst_tableaux_add_cells (_sst_result, right_tableaux, real_sz_right);
}

void
__sst_tableaux_multiply (const __sst_tableaux_t *_sst_left,
                         const __sst_tableaux_t *_sst_right,
                         __sst_tableaux_t *      _sst_result)
{
  size_t sz_right = __sst_tableaux_storage_size (_sst_right);
  __sst_tableaux_fast_multiply (_sst_left, _sst_right, sz_right, _sst_result);
}

static bool
tableaux_equals (const __sst_tableaux_t *_sst_left,
                 const size_t            _sst_left_sz,
                 const __sst_tableaux_t *_sst_right,
                 const size_t            _sst_right_sz)
{
  if (_sst_left_sz != _sst_right_sz)
  {
    return false;
  }

  __tableaux_cell_t left_cells[_sst_left_sz];
  __tableaux_cell_t right_cells[_sst_right_sz];

  __sst_tableaux_read_to_compressed_tableaux (_sst_left, left_cells);
  __sst_tableaux_read_to_compressed_tableaux (_sst_right, right_cells);

  for (size_t i = 0; i < _sst_left_sz; i++)
  {
    if (left_cells[i].val != right_cells[i].val
        || left_cells[i].len != right_cells[i].len)
    {
      return false;
    }
  }
  return true;
}

bool
__sst_tableaux_check_identity (size_t *x,
                               size_t  len_x,
                               size_t *y,
                               size_t  len_y,
                               size_t *assigns,
                               size_t  nr_vars,
                               void *  elems)
{
  __sst_word_tableaux_t *tableaux = (__sst_word_tableaux_t *) elems;

  __sst_word_tableaux_t left_side[len_x];
  __sst_word_tableaux_t right_side[len_y];

  size_t len_left  = 0;
  size_t len_right = 0;

  for (size_t i = 0; i < len_x; i++)
  {
    __sst_word_tableaux_t curr = tableaux[assigns[x[i]]];
    left_side[i]               = curr;
    len_left                   = len_left + curr.counter;
  }

  for (size_t i = 0; i < len_y; i++)
  {
    __sst_word_tableaux_t curr = tableaux[assigns[y[i]]];
    right_side[i]              = curr;
    len_right                  = len_right + curr.counter;
  }

  __tableaux_cell_t left_cells[len_left];
  __tableaux_cell_t right_cells[len_right];

  __sst_word_tableaux_t left = {
    .size = len_left, .counter = len_left, .cells = left_cells};

  __sst_word_tableaux_t right = {
    .size = len_right, .counter = len_right, .cells = right_cells};

  for (size_t i = 0; i < len_x; i++)
  {
    memcpy (&(left.cells[i]),
            &(left_side[i].cells),
            sizeof (__tableaux_cell_t) * left_side[i].counter);
  }

  for (size_t i = 0; i < len_y; i++)
  {
    memcpy (&(right.cells[i]),
            &(right_side[i].cells),
            sizeof (__tableaux_cell_t) * right_side[i].counter);
  }

  __sst_tableaux_t *l = __sst_tableaux_create ();
  __sst_tableaux_t *r = __sst_tableaux_create ();

  __sst_tableaux_read_from_compressed_tableaux (l, left.cells, left.counter);
  __sst_tableaux_read_from_compressed_tableaux (r, right.cells, right.counter);

  return tableaux_equals (l, left.counter, r, right.counter);
}

static ptrdiff_t
__sst_tableaux_read_to_plain_iteration_function (__tableaux_cell_t cell,
                                                 size_t            index,
                                                 size_t            real_index,
                                                 void *            data)
{
  __tableaux_cell_val_t *vector = (__tableaux_cell_val_t *) data;
  for (size_t i = 0; i < cell.len; i++)
  {
    vector[real_index + i] = cell.val;
  }
  return (ptrdiff_t) 1;
}

void
__sst_tableaux_read_to_plain_tableaux (
  const __sst_tableaux_t *_sst, __tableaux_cell_val_t *_sst_tableaux_cells)
{
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_read_to_plain_iteration_function, _sst_tableaux_cells);
}

void
__sst_tableaux_read_from_plain_tableaux (
  __sst_tableaux_t *           _sst,
  const __tableaux_cell_val_t *_sst_tableaux_cells,
  const size_t                 len)
{
  __tableaux_cell_val_t curr  = len > 0 ? _sst_tableaux_cells[0] : 0;
  size_t                count = 0;
  for (size_t i = 0; i < len; i++)
  {
    if (_sst_tableaux_cells[i] == curr)
    {
      count++;
    } else
    {
      __tableaux_cell_t cell = {.val = curr, .len = count};
      __sst_tableaux_add_cells (_sst, &cell, count);
      curr  = _sst_tableaux_cells[i];
      count = 1;
    }
  }
}

static ptrdiff_t
__sst_tableaux_read_to_compressed_iteration_function (__tableaux_cell_t cell,
                                                      size_t            index,
                                                      size_t real_index,
                                                      void * data)
{
  __tableaux_cell_t *vector = (__tableaux_cell_t *) data;
  vector[real_index]        = cell;
  return (ptrdiff_t) 1;
}

size_t
__sst_tableaux_read_to_compressed_tableaux (
  const __sst_tableaux_t *_sst, __tableaux_cell_t *_sst_tableaux_cells)
{
  return __sst_tableaux_iterate_tableaux (
    _sst,
    __sst_tableaux_read_to_compressed_iteration_function,
    _sst_tableaux_cells);
}

void
__sst_tableaux_read_from_compressed_tableaux (
  __sst_tableaux_t *       _sst,
  const __tableaux_cell_t *_sst_tableaux_cells,
  const size_t             len)
{
  __tableaux_cell_val_t curr  = len > 0 ? _sst_tableaux_cells[0].val : 0;
  size_t                count = 0;
  for (size_t i = 0; i < len; i++)
  {
    if (_sst_tableaux_cells[i].val == curr)
    {
      count += _sst_tableaux_cells[i].len;
    } else
    {
      __tableaux_cell_t cell = {.val = curr, .len = count};
      __sst_tableaux_add_cells (_sst, &cell, count);
      curr  = _sst_tableaux_cells[i].val;
      count = _sst_tableaux_cells[i].len;
    }
  }
}

__sst_tableaux_t *
__sst_tableaux_read_plain_file (const char *filename)
{
  FILE *                 f     = fopen (filename, "r");
  size_t                 sz    = (1 << 5);
  size_t                 count = 0;
  __tableaux_cell_val_t *plain = malloc (sz * sizeof (__tableaux_cell_val_t));

  while (fscanf (f, "%lu", &(plain[count++])) != EOF)
  {
    if (count == sz)
    {
      sz    = sz << 1;
      plain = realloc (plain, sz * sizeof (__tableaux_cell_val_t));
    }
  }
  __sst_tableaux_t *_sst = __sst_tableaux_create ();
  __sst_tableaux_read_from_plain_tableaux (_sst, plain, count);
  return _sst;
}

static ptrdiff_t
__sst_tableaux_write_plain_file_iterator_function (__tableaux_cell_t cell,
                                                   size_t            index,
                                                   size_t            real_index,
                                                   void *            data)
{
  FILE *f = (FILE *) data;
  for (size_t i = 0; i < cell.len; i++)
  {
    fprintf (f, "%lu\n", cell.val);
  }
  return (ptrdiff_t) 1;
}

void
__sst_tableaux_write_plain_file (const __sst_tableaux_t *_sst,
                                 const char *            filename)
{
  FILE *f = fopen (filename, "w");
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_write_plain_file_iterator_function, f);
  fclose (f);
}

__sst_tableaux_t *
__sst_tableaux_read_compressed_file (const char *filename)
{
  FILE *             f     = fopen (filename, "r");
  size_t             sz    = (1 << 5);
  size_t             count = 0;
  __tableaux_cell_t *cells = malloc (sz * sizeof (__tableaux_cell_t));

  while (fscanf (f, "%lu %lu", &(cells[count].val), &(cells[count].len)) != EOF)
  {
    count++;
    if (count == sz)
    {
      sz    = sz << 1;
      cells = realloc (cells, sz * sizeof (__tableaux_cell_t));
    }
  }
  __sst_tableaux_t *_sst = __sst_tableaux_create ();
  __sst_tableaux_read_from_compressed_tableaux (_sst, cells, count);
  return _sst;
}

static ptrdiff_t
__sst_tableaux_write_compressed_file_iterator_function (__tableaux_cell_t cell,
                                                        size_t            index,
                                                        size_t real_index,
                                                        void * data)
{
  FILE *f = (FILE *) data;
  fprintf (f, "%lu %lu\n", cell.val, cell.len);
  return (ptrdiff_t) 1;
}

void
__sst_tableaux_write_compressed_file (const __sst_tableaux_t *_sst,
                                      const char *            filename)
{
  FILE *f = fopen (filename, "w");
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_write_compressed_file_iterator_function, f);
  fclose (f);
}

void
__sst_tableaux_print (const __sst_tableaux_t *_sst)
{
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      for (size_t k = 0; k < _sst->rows[i].array[j].len; k++)
      {
        printf ("%lu, ", _sst->rows[i].array[j].val);
      }
    }
    printf ("\n");
  }
}

#endif    // __SST_TABLEAUX__
