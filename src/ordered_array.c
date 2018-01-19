#include "ordered_array.h"

#ifdef __PM_ORDERED_ARRAY__

void
__pm_ordered_array_create (__pm_ordered_array_t *_pmoa)
{
  _pmoa->size    = __PM_ORDERED_ARRAY_DEFAULT_SIZE;
  _pmoa->counter = 0;
  _pmoa->array   = malloc (_pmoa->size * sizeof (__matroid_cell_t));
}

void
__pm_ordered_array_destroy (__pm_ordered_array_t *_pmoa)
{
  _pmoa->size = _pmoa->counter = 0;
  free (_pmoa->array);
}

static void
__pm_ordered_array_resize (__pm_ordered_array_t *_pmoa)
{
  _pmoa->size = (_pmoa->size + 1) << 1;    // multiplication by two
  _pmoa->array =
    realloc (_pmoa->array, _pmoa->size * sizeof (__matroid_cell_t));
}

__pm_ordered_array_place_result_t
__pm_ordered_array_place (__pm_ordered_array_t * _pmoa,
                          const __matroid_cell_t to_place,
                          __matroid_cell_t *     replaced)
{
  if (_pmoa->counter == 0
      || to_place.val >= _pmoa->array[_pmoa->counter - 1].val)
  {
    if (_pmoa->counter == _pmoa->size)
    {
      __pm_ordered_array_resize (_pmoa);
    }
    _pmoa->array[_pmoa->counter++] = to_place;
    return APPENDED;
  }

  size_t top    = _pmoa->counter - 1;
  size_t bottom = 0;
  size_t mid    = (top + bottom) >> 1;
  bool   found  = false;

  while (!found)
  {
    if (to_place.val < _pmoa->array[mid].val)
    {
      top = mid;
    } else
    {
      bottom = mid;
    }
    found = to_place.val < _pmoa->array[mid].val
            && (mid == 0 || to_place.val >= _pmoa->array[mid - 1].val);
    mid = (top + bottom) >> 1;
  }

  *replaced         = _pmoa->array[mid];
  _pmoa->array[mid] = to_place;
  return REPLACED;
}

static void
__pm_ordered_array_resize_to (__pm_ordered_array_t *_pmoa, const size_t sz)
{
  _pmoa->size = sz;
  _pmoa->array =
    realloc (_pmoa->array, _pmoa->size * sizeof (__matroid_cell_t));
}

void
__pm_ordered_array_copy (const __pm_ordered_array_t *_pmoa_from,
                         __pm_ordered_array_t *      _pmoa_to)
{
  if (__builtin_expect (_pmoa_from->counter >= _pmoa_to->size, 0))
  {
    __pm_ordered_array_resize_to (_pmoa_to, _pmoa_from->size);
  }
  memcpy (_pmoa_to->array,
          _pmoa_from->array,
          _pmoa_from->counter * sizeof (__matroid_cell_t));
  _pmoa_to->counter = _pmoa_from->counter;
}

#endif    // __PM_ORDERED_ARRAY__
