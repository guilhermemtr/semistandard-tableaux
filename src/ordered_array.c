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

size_t
__sst_ordered_array_real_length (__sst_ordered_array_t *_sstoa)
{
  size_t size = 0;
  for (size_t i = 0; i < _sstoa->counter; i++)
  {
    size += _sstoa->array[i].len;
  }
  return size;
}

void
__sst_ordered_array_resize_to (__sst_ordered_array_t *_sstoa, const size_t sz)
{
  _sstoa->size = sz;
  _sstoa->array =
    realloc (_sstoa->array, _sstoa->size * sizeof (__tableaux_cell_t));
}

void
__sst_ordered_array_resize (__sst_ordered_array_t *_sstoa)
{
  __sst_ordered_array_resize_to(_sstoa, (_sstoa->size + 1) << 1);
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
