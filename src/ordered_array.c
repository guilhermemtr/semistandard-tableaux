#include "ordered_array.h"

#ifdef __SST_ORDERED_ARRAY__

void
__sst_ordered_array_create (__sst_ordered_array_t *_sstoa)
{
  _sstoa->size    = __SST_ORDERED_ARRAY_DEFAULT_SIZE;
  _sstoa->counter = 0;
  _sstoa->array   = malloc (_sstoa->size * sizeof (__tableaux_cell_t));
}

void
__sst_ordered_array_destroy (__sst_ordered_array_t *_sstoa)
{
  _sstoa->size = _sstoa->counter = 0;
  free (_sstoa->array);
}

static void
__sst_ordered_array_resize (__sst_ordered_array_t *_sstoa)
{
  _sstoa->size = (_sstoa->size + 1) << 1;    // multiplication by two
  _sstoa->array =
    realloc (_sstoa->array, _sstoa->size * sizeof (__tableaux_cell_t));
}

__sst_ordered_array_place_result_t
__sst_ordered_array_place (__sst_ordered_array_t * _sstoa,
                          const __tableaux_cell_t to_place,
                          __tableaux_cell_t *     replaced)
{
  if (_sstoa->counter == 0
      || to_place.val >= _sstoa->array[_sstoa->counter - 1].val)
  {
    if (_sstoa->counter == _sstoa->size)
    {
      __sst_ordered_array_resize (_sstoa);
    }
    _sstoa->array[_sstoa->counter++] = to_place;
    return APPENDED;
  }

  size_t top    = _sstoa->counter - 1;
  size_t bottom = 0;
  size_t mid    = (top + bottom + 1) >> 1;

  while (true)
  {
    if (to_place.val < _sstoa->array[mid].val
        && (mid == 0 || to_place.val >= _sstoa->array[mid - 1].val))
    {
      break;
    }

    if (to_place.val < _sstoa->array[mid].val)
    {
      top = mid;
    } else
    {
      bottom = mid;
    }

    mid = (top + bottom + 1) >> 1;
  }

  *replaced         = _sstoa->array[mid];
  _sstoa->array[mid] = to_place;
  return REPLACED;
}

static void
__sst_ordered_array_resize_to (__sst_ordered_array_t *_sstoa, const size_t sz)
{
  _sstoa->size = sz;
  _sstoa->array =
    realloc (_sstoa->array, _sstoa->size * sizeof (__tableaux_cell_t));
}

void
__sst_ordered_array_copy (const __sst_ordered_array_t *_sstoa_from,
                         __sst_ordered_array_t *      _sstoa_to)
{
  if (__builtin_expect (_sstoa_from->counter >= _sstoa_to->size, 0))
  {
    __sst_ordered_array_resize_to (_sstoa_to, _sstoa_from->size);
  }
  memcpy (_sstoa_to->array,
          _sstoa_from->array,
          _sstoa_from->counter * sizeof (__tableaux_cell_t));
  _sstoa_to->counter = _sstoa_from->counter;
}

#endif    // __SST_ORDERED_ARRAY__
