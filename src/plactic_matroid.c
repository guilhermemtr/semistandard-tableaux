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

void
__pm_matroid_init (const __pm_matroid_t *      _pm,
                   const __matroid_cell_val_t *_pm_values,
                   const size_t                sz)
{
}

void
__pm_matroid_destroy (const __pm_matroid_t *_pm)
{
  for (size_t i = 0; i < _pm->counter; i++)
  {
    __pm_ordered_array_destroy (_pm->columns[i]);
    free (_pm->columns[i]);
  }
  free (_pm->columns);
  free (_pm);
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

static void
__pm_matroid_resize (__pm_matroid_t *_pm)
{
  _pm->size    = 2 * (_pm->size + 1);
  _pm->columns = realloc (_pm->size * sizeof (__pm_ordered_array_t));
}

void
__pm_matroid_add_cell (const __pm_matroid_t *_pm, const __matroid_cell_t cell)
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
    res = __pm_ordered_array_place (_pm->columns[j++], to_place, &replaced);
    to_place = replaced;
  }
}

size_t
__pm_matroid_read_matroid (const __pm_matroid_t *       _pm,
                           const __matroid_cell_val_t **_pm_matroid_cells)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _pm->counter; i++)
  {
    total_size += _pm->columns[i].counter;
  }
  *_pm_matroid_cells = malloc (total_size * sizeof (__matroid_cell_val_t));
  size_t i           = 0;
  size_t j           = _pm->counter - 1;
  size_t pos         = 0;
  while (i <= _pm->columns[0].counter)
  {
    while (j >= 0)
    {
      *_pm_matroid_cells[pos++] = _pm->columns[j].array[i];
      j--;
    }
    j = _pm->counter - 1;
    i++;
  }
  return total_size;
}

void
__pm_matroid_apply_tag (const __pm_matroid_t *     _pm,
                        const __matroid_cell_tag_t tag)
{
  for (size_t j = 0; j < _pm->counter; j++)
  {
    for (size_t i = 0; i < _pm->columns[j].counter; i++)
    {
      _pm->columns[j].array[i].tag = tag;
    }
  }
}

void
__pm_matroid_multiply (const __pm_matroid_t *_pm_left,
                       const __pm_matroid_t *_pm_right,
                       const __pm_matroid_t *_pm_result)
{
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

#endif    // __PM_MATROID__
