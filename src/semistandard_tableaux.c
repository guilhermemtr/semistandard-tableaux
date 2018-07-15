#include "semistandard_tableaux.h"

#ifdef __SST_TABLEAUX__

static void
__sst_tableaux_initialize_rows (__sst_t *_sst)
{
  for (size_t i = _sst->counter; i < _sst->size; i++)
  {
    __sst_ordered_array_init (&(_sst->rows[i]));
  }
}

__sst_t *
__sst_tableaux_create (void)
{
  __sst_t *tableaux = malloc (sizeof (__sst_t));
  tableaux->size    = __SST_ORDERED_ARRAY_DEFAULT_SIZE;
  tableaux->counter = 0;
  tableaux->rows    = malloc (tableaux->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (tableaux);
  return tableaux;
}

__sst_t *
__sst_tableaux_table_create (const __sst_word_t *_wsst)
{
  __sst_t *t = __sst_tableaux_create ();
  __sst_tableaux_read_from_compressed_tableaux (
    t, _wsst->cells, _wsst->counter);
  return t;
}

__sst_t *
__sst_tableaux_duplicate (const __sst_t *t)
{
  __sst_t *tableaux = malloc (sizeof (__sst_t));
  tableaux->size    = t->size;
  tableaux->counter = t->counter;
  tableaux->rows    = malloc (tableaux->size * sizeof (__sst_ordered_array_t));
  for (size_t i = 0; i < t->counter; i++)
  {
    __sst_ordered_array_duplicate (&(t->rows[i]), &(tableaux->rows[i]));
  }
  __sst_tableaux_initialize_rows (tableaux);
  return tableaux;
}

static void
__sst_tableaux_resize_to (__sst_t *_sst, const size_t sz)
{
  _sst->size = sz;
  _sst->rows =
    realloc (_sst->rows, _sst->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (_sst);
}

static size_t
__sst_tableaux_add_cells (__sst_t *                _sst,
                          const __tableaux_cell_t *cells,
                          size_t                   real_nr_cells)
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
        __sst_tableaux_resize_to (_sst, (_sst->size + 1) << 2);
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
__sst_tableaux_init (__sst_t *          _sst,
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
__sst_tableaux_destroy (__sst_t *_sst)
{
  for (size_t i = 0; i < _sst->size; i++)
  {
    __sst_ordered_array_destroy (&(_sst->rows[i]));
  }
  free (_sst->rows);
  free (_sst);
}

size_t
__sst_tableaux_iterate_tableaux (const __sst_t *    _sst,
                                 iteration_function fn,
                                 void *             data)
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
__sst_tableaux_size (const __sst_t *_sst)
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
__sst_tableaux_storage_size (const __sst_t *_sst)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    total_size += _sst->rows[i].counter;
  }
  return total_size;
}

bool
__sst_tableaux_equals (const __sst_t *_sst_left, const __sst_t *_sst_right)
{
  if (_sst_left->counter != _sst_right->counter)
  {
    return false;
  }

  for (size_t i = 0; i < _sst_left->counter; i++)
  {
    if (_sst_left->rows[i].counter != _sst_right->rows[i].counter)
    {
      return false;
    }
    for (size_t j = 0; j < _sst_left->rows[i].counter; j++)
    {
      __tableaux_cell_t l_cell = _sst_left->rows[i].array[j];
      __tableaux_cell_t r_cell = _sst_right->rows[i].array[j];
      if (l_cell.val != r_cell.val || l_cell.len != r_cell.len)
      {
        return false;
      }
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
  __sst_t **tableaux = (__sst_t **) elems;

  __sst_t *left_curr = __sst_tableaux_duplicate (tableaux[assigns[x[0]]]);
  __sst_t *left_res  = __sst_tableaux_create ();

  __sst_t *right_curr = __sst_tableaux_duplicate (tableaux[assigns[y[0]]]);
  __sst_t *right_res  = __sst_tableaux_create ();

  for (size_t i = 1; i < len_x; i++)
  {
    __sst_tableaux_multiply (left_curr, tableaux[assigns[x[i]]], left_res);
    __sst_t *tmp = left_res;
    left_res     = left_curr;
    left_curr    = tmp;
  }

  for (size_t i = 1; i < len_y; i++)
  {
    __sst_tableaux_multiply (right_curr, tableaux[assigns[y[i]]], right_res);
    __sst_t *tmp = right_res;
    right_res    = right_curr;
    right_curr   = tmp;
  }

  bool identity_checks = __sst_tableaux_equals (left_res, right_res);

  __sst_tableaux_destroy (left_curr);
  __sst_tableaux_destroy (left_res);
  __sst_tableaux_destroy (right_curr);
  __sst_tableaux_destroy (right_res);

  return identity_checks;
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
  const __sst_t *_sst, __tableaux_cell_val_t *_sst_tableaux_cells)
{
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_read_to_plain_iteration_function, _sst_tableaux_cells);
}

void
__sst_tableaux_read_from_plain_tableaux (
  __sst_t *                    _sst,
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
  vector[index]             = cell;
  return (ptrdiff_t) 1;
}

size_t
__sst_tableaux_read_to_compressed_tableaux (
  const __sst_t *_sst, __tableaux_cell_t *_sst_tableaux_cells)
{
  __sst_tableaux_iterate_tableaux (
    _sst,
    __sst_tableaux_read_to_compressed_iteration_function,
    _sst_tableaux_cells);
  return __sst_tableaux_storage_size (_sst);
}

void
__sst_tableaux_read_from_compressed_tableaux (
  __sst_t *_sst, const __tableaux_cell_t *_sst_tableaux_cells, const size_t len)
{
  size_t real_len = 0;
  for (size_t i = 0; i < len; i++)
  {
    real_len += _sst_tableaux_cells[i].len;
  }
  __sst_tableaux_add_cells (_sst, _sst_tableaux_cells, real_len);
}

__sst_t *
__sst_tableaux_read_plain_file (const char *filename)
{
  FILE *f = fopen (filename, "r");
  if (f == NULL)
  {
    return NULL;
  }
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

  fclose (f);

  __sst_t *_sst = __sst_tableaux_create ();
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
__sst_tableaux_write_plain_file (const __sst_t *_sst, const char *filename)
{
  FILE *f = fopen (filename, "w");
  if (f == NULL)
  {
    return;
  }
  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_write_plain_file_iterator_function, f);
  fclose (f);
}

__sst_t *
__sst_tableaux_read_compressed_file (const char *filename)
{
  FILE *f = fopen (filename, "r");

  if (f == NULL)
  {
    return NULL;
  }

  size_t             sz    = (1 << 5);
  size_t             count = 0;
  __tableaux_cell_t *cells = malloc (sz * sizeof (__tableaux_cell_t));

  int read = 0;
  while (
    (read = fscanf (f, "%lu %lu", &(cells[count].val), &(cells[count].len)))
    != EOF)
  {
    count++;
    if (count == sz)
    {
      sz    = sz << 1;
      cells = realloc (cells, sz * sizeof (__tableaux_cell_t));
    }
  }

  fclose (f);

  __sst_t *_sst = __sst_tableaux_create ();
  __sst_tableaux_read_from_compressed_tableaux (_sst, cells, count);
  return _sst;
}

__sst_t *
__sst_tableaux_read_table_format_file (const char *filename)
{
  FILE *f = fopen (filename, "r");

  if (f == NULL)
  {
    return NULL;
  }

  size_t             sz    = (1 << 5);
  size_t             count = 0;
  __tableaux_cell_t *cells = malloc (sz * sizeof (__tableaux_cell_t));

  int read = 0;
  while (
    (read = fscanf (f, "%lu %lu", &(cells[count].val), &(cells[count].len)))
    != EOF)
  {
    count++;
    if (count == sz)
    {
      sz    = sz << 1;
      cells = realloc (cells, sz * sizeof (__tableaux_cell_t));
    }
  }
  fclose (f);
  __sst_t *_sst = __sst_tableaux_create ();
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
__sst_tableaux_write_compressed_file (const __sst_t *_sst, const char *filename)
{
  FILE *f = fopen (filename, "w");

  if (f == NULL)
  {
    return;
  }

  __sst_tableaux_iterate_tableaux (
    _sst, __sst_tableaux_write_compressed_file_iterator_function, f);
  fclose (f);
}

// Different functions because of different types of return values
static __tableaux_cell_val_t
__sst_tableaux_get_max_val_tableaux (const __sst_t *_sst)
{
  __tableaux_cell_val_t max = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      __tableaux_cell_val_t v = _sst->rows[i].array[j].val;
      max                     = max >= v ? max : v;
    }
  }
  return max;
}

static __tableaux_cell_len_t
__sst_tableaux_get_max_len_tableaux (const __sst_t *_sst)
{
  __tableaux_cell_len_t max = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      __tableaux_cell_len_t l = _sst->rows[i].array[j].len;
      max                     = max >= l ? max : l;
    }
  }
  return max;
}

static size_t
__sst_tableaux_get_val_len (__tableaux_cell_val_t v)
{
  size_t len = 0;
  do
  {
    len++;
    v = v / 10;
  } while (v != 0);
  return len;
}

static size_t
__sst_tableaux_get_len_len (__tableaux_cell_len_t v)
{
  size_t len = 0;
  do
  {
    len++;
    v = v / 10;
  } while (v != 0);
  return len;
}

static void
__sst_tableaux_print_val (__tableaux_cell_val_t v,
                          size_t                max_val_len,
                          FILE *                out)
{
  size_t v_len = __sst_tableaux_get_val_len (v);
  for (size_t i = v_len; i < max_val_len; i++)
  {
    fprintf (out, " ");
  }
  fprintf (out, __TABLEAUX_CELL_VAL_FORMAT, v);
}

static void
__sst_tableaux_print_len (__tableaux_cell_len_t l,
                          size_t                max_len_len,
                          FILE *                out)
{
  size_t l_len = __sst_tableaux_get_len_len (l);
  for (size_t i = l_len; i < max_len_len; i++)
  {
    fprintf (out, " ");
  }
  fprintf (out, __TABLEAUX_CELL_LEN_FORMAT, l);
}

static void
__sst_tableaux_plain_print_out (const __sst_t *_sst, FILE *out)
{
  size_t max_val_len =
    __sst_tableaux_get_val_len (__sst_tableaux_get_max_val_tableaux (_sst));
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      for (size_t k = 0; k < _sst->rows[i].array[j].len; k++)
      {
        __sst_tableaux_print_val (_sst->rows[i].array[j].val, max_val_len, out);
        fprintf (out, " ");
      }
    }
    fprintf (out, "\n");
  }
}


__sst_t *
__sst_tableaux_read_table_file (const char *filename)
{
  FILE *f = fopen (filename, "r");

  if (f == NULL)
  {
    return NULL;
  }

  ssize_t  read;
  char *   line     = NULL;
  size_t   len      = 0;
  char *   save_ptr = NULL;
  __sst_t *tableaux = malloc (sizeof (__sst_t));
  tableaux->size    = __SST_ORDERED_ARRAY_DEFAULT_SIZE;
  tableaux->counter = 0;
  tableaux->rows    = malloc (tableaux->size * sizeof (__sst_ordered_array_t));
  __sst_tableaux_initialize_rows (tableaux);

  while ((read = getline (&line, &len, f)) != -1)
  {
    __tableaux_cell_val_t v;
    char *                tmp = line;
    char *                res;
    while ((res = strtok_r (tmp, " ", &save_ptr)) != NULL)
    {
      tmp = NULL;

      if (tableaux->counter == tableaux->size)
      {
        __sst_tableaux_resize_to (tableaux, (tableaux->size + 1) << 1);
        __sst_tableaux_initialize_rows (tableaux);
      }

      if (sscanf (res, __TABLEAUX_CELL_VAL_FORMAT, &v) >= 0)
      {
        __tableaux_cell_t  c        = {.val = v, .len = 1};
        __tableaux_cell_t *tmp      = NULL;
        size_t             replaced = 0;
        __sst_ordered_array_place (
          &(tableaux->rows[tableaux->counter]), &c, 1, tmp, &replaced);
      }
    }

    free (line);
    line = NULL;
    tableaux->counter++;
  }

  fclose (f);

  return tableaux;
}

void
__sst_tableaux_write_table_file (const __sst_t *_sst, const char *filename)
{
  FILE *f = fopen (filename, "w");
  if (f == NULL)
  {
    return;
  }
  __sst_tableaux_plain_print_out (_sst, f);
  fclose (f);
}

void
__sst_tableaux_print (const __sst_t *_sst)
{
  size_t max_val_len =
    __sst_tableaux_get_val_len (__sst_tableaux_get_max_val_tableaux (_sst));
  size_t max_len_len =
    __sst_tableaux_get_len_len (__sst_tableaux_get_max_len_tableaux (_sst));
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      printf ("(");
      __sst_tableaux_print_val (
        _sst->rows[i].array[j].val, max_val_len, stdout);
      printf (",");
      __sst_tableaux_print_len (
        _sst->rows[i].array[j].len, max_len_len, stdout);
      printf (") ");
    }
    printf ("\n");
  }
}

void
__sst_tableaux_plain_print (const __sst_t *_sst)
{
  __sst_tableaux_plain_print_out (_sst, stdout);
}

bool
__sst_tableaux_check (const __sst_t *_sst)
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
    size_t curr = __sst_ordered_array_size (&(_sst->rows[j]));
    ok          = ok && prev >= curr;
    prev        = curr;
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
               || _sst->rows[j].array[i].val <= _sst->rows[j].array[i + 1].val);
      ok = ok
           && (j + 1 >= _sst->counter || i >= _sst->rows[j].counter
               || _sst->rows[j].array[i].val < _sst->rows[j + 1].array[i].val);

      if (!ok)
      {
        return ok;
      }
    }
  }
  return ok;
}

size_t
__sst_tableaux_fast_multiply (const __sst_t *_sst_left,
                              const __sst_t *_sst_right,
                              const size_t   sz_right,
                              __sst_t *      _sst_result)
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
__sst_tableaux_multiply (const __sst_t *_sst_left,
                         const __sst_t *_sst_right,
                         __sst_t *      _sst_result)
{
  size_t sz_right = __sst_tableaux_storage_size (_sst_right);
  __sst_tableaux_fast_multiply (_sst_left, _sst_right, sz_right, _sst_result);
}

__sst_t *
__sst_tableaux_read (const char *filename)
{
  char *   fn  = __utils_get_filename (filename, sstt);
  __sst_t *res = __sst_tableaux_read_table_format_file (fn);
  free (fn);
  return res;
}

void
__sst_tableaux_write (const __sst_t *_sst, const char *filename)
{
  char *fn = __utils_get_filename (filename, sstt);
  __sst_tableaux_write_table_file (_sst, fn);
  free (fn);
}

__tuple_entry_data_t *
__sst_tableaux_entry_data_create (__sst_t *m)
{
  __tuple_entry_data_t *entry = malloc (sizeof (__tuple_entry_data_t));
  entry->e                    = __sst_tableaux_duplicate (m);
  entry->type                 = sstt;
  entry->tester  = (__ap_identity_tester *) __sst_tableaux_check_identity;
  entry->equals  = (__ap_equals *) __sst_tableaux_equals;
  entry->destroy = (__ap_op *) __sst_tableaux_destroy;
  entry->print   = (__ap_op *) __sst_tableaux_print;
  entry->mult    = (__ap_mult *) __sst_tableaux_multiply;
  entry->clone   = (__ap_clone *) __sst_tableaux_duplicate;
  entry->read    = (__ap_read *) __sst_tableaux_read;
  entry->write   = (__ap_write *) __sst_tableaux_write;
  entry->entry_generator =
    (__ap_tuple_entry_data_create *) __sst_tableaux_entry_data_create;
  return entry;
}

#endif    // __SST_TABLEAUX__
