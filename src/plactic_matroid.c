#include "plactic_matroid.h"

#ifdef __PM_MATROID__

__pm_matroid_t *
__pm_matroid_create (void)
{
  __pm_matroid_t *matroid = malloc (sizeof (__pm_matroid_t));
  matroid->size           = __PM_ORDERED_ARRAY_DEFAULT_SIZE;
  matroid->counter        = 0;
  matroid->columns = malloc (matroid->size * sizeof (__pm_ordered_array_t));
  return matroid;
}

static void
__pm_matroid_resize (__pm_matroid_t *_pm)
{
  _pm->size = (_pm->size + 1) << 1;    // multiplication by two
  _pm->columns =
    realloc (_pm->columns, _pm->size * sizeof (__pm_ordered_array_t));
}

static void
__pm_matroid_add_cell (__pm_matroid_t *_pm, const __matroid_cell_t cell)
{
  __pm_ordered_array_place_result_t res      = REPLACED;
  __matroid_cell_t                  to_place = cell;
  __matroid_cell_t                  replaced;
  size_t                            j = 0;
  while (res != APPENDED)
  {
    if (j == _pm->size)
    {
      __pm_matroid_resize (_pm);
    }
    res = __pm_ordered_array_place (&(_pm->columns[j++]), to_place, &replaced);
    to_place = replaced;
  }
}

void
__pm_matroid_init (__pm_matroid_t *        _pm,
                   const __matroid_cell_t *_pm_values,
                   const size_t            sz)
{
  for (size_t i = 0; i < sz; i++)
  {
    __pm_matroid_add_cell (_pm, _pm_values[i]);
  }
}

void
__pm_matroid_destroy (__pm_matroid_t *_pm)
{
  for (size_t i = 0; i < _pm->counter; i++)
  {
    __pm_ordered_array_destroy (&(_pm->columns[i]));
  }
  free (_pm->columns);
  free (_pm);
}

void
__pm_matroid_iterate_matroid (const __pm_matroid_t *   _pm,
                              iteration_function fn,
                              void *             data)
{
  size_t index = 0;
  size_t i     = 0;
  size_t j     = _pm->counter - 1;
  while (i <= _pm->columns[0].counter)
  {
    while (j >= 0)
    {
      ptrdiff_t offset = fn (_pm->columns[j].array[i], index++, data);
      if (offset != 1)
      {
        abort ();    // not yet implemented
      }
      j--;
    }
    j = _pm->counter - 1;
    i++;
  }
}

size_t
__pm_matroid_size (const __pm_matroid_t *_pm)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _pm->counter; i++)
  {
    total_size += _pm->columns[i].counter;
  }
  return total_size;
}

static ptrdiff_t
__pm_matroid_read_iteration_function (__matroid_cell_t cell,
                                      size_t           index,
                                      void *           data)
{
  __matroid_cell_val_t *vector = (__matroid_cell_val_t *) data;
  vector[index]                = cell.val;
  return (ptrdiff_t) 1;
}

size_t
__pm_matroid_read_matroid (const __pm_matroid_t *       _pm,
                           const __matroid_cell_val_t **_pm_matroid_cells)
{
  size_t total_size  = __pm_matroid_size (_pm);
  *_pm_matroid_cells = malloc (total_size * sizeof (__matroid_cell_val_t));
  __pm_matroid_iterate_matroid (
    _pm, __pm_matroid_read_iteration_function, _pm_matroid_cells);
  return total_size;
}

void
__pm_matroid_apply_tag (__pm_matroid_t *_pm, const __matroid_cell_tag_t tag)
{
  for (size_t j = 0; j < _pm->counter; j++)
  {
    for (size_t i = 0; i < _pm->columns[j].counter; i++)
    {
      _pm->columns[j].array[i].tag = tag;
    }
  }
}

static ptrdiff_t
__pm_matroid_multiply_iteration_function (const __matroid_cell_t cell,
                                          const size_t           index,
                                          void *                 data)
{
  __pm_matroid_t *_pm_result = (__pm_matroid_t *) data;
  __pm_matroid_add_cell (_pm_result, cell);
  return (ptrdiff_t) 1;
}

static void
__pm_matroid_resize_to (__pm_matroid_t *_pm, const size_t sz)
{
  _pm->size = sz;
  _pm->columns =
    realloc (_pm->columns, _pm->size * sizeof (__pm_ordered_array_t));
}

void
__pm_matroid_multiply (const __pm_matroid_t *_pm_left,
                       const __pm_matroid_t *_pm_right,
                       __pm_matroid_t *      _pm_result)
{
  _pm_result->counter = 0;
  if (__builtin_expect (_pm_left->counter >= _pm_result->size, 0))
  {
    __pm_matroid_resize_to (_pm_result, _pm_left->counter);
  }

  for (size_t i = 0; i < _pm_left->counter; i++)
  {
    __pm_ordered_array_copy (&_pm_left->columns[i], &_pm_result->columns[i]);
  }

  __pm_matroid_iterate_matroid (
    _pm_right, __pm_matroid_multiply_iteration_function, _pm_result);
}

bool
__pm_matroid_check (const __pm_matroid_t *_pm)
{
  bool ok = true;

  // first, check sizes
  if (_pm->counter == 0)
  {
    return ok;
  }

  size_t prev = _pm->columns[0].counter;
  for (size_t j = 0; j < _pm->counter; j++)
  {
    ok   = ok && prev >= _pm->columns[j].counter;
    prev = _pm->columns[j].counter;
    if (!ok)
    {
      return ok;
    }
  }

  // second, check value constraints
  for (size_t j = 0; j < _pm->counter; j++)
  {
    for (size_t i = 0; i < _pm->columns[j].counter; i++)
    {
      ok = ok
           && (i + 1 >= _pm->columns[j].counter
               || _pm->columns[j].array[i].val
                    <= _pm->columns[j].array[i + 1].val);
      ok = ok
           && (j + 1 >= _pm->counter
               || _pm->columns[j + 1].array[i].val
                    < _pm->columns[j + 1].array[i].val);

      if (!ok)
      {
        return ok;
      }
    }
  }
  return ok;
}

__pm_matroid_t *
__pm_matroid_read_file (const char *filename)
{
  return NULL;
}

void
__pm_matroid_write_file (const __pm_matroid_t *_pm, const char *filename)
{
}

#endif    // __PM_MATROID__
