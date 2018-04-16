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
  _sstoa->size = sz >= _sstoa->counter ? sz : _sstoa->counter;
  _sstoa->array =
    realloc (_sstoa->array, _sstoa->size * sizeof (__tableaux_cell_t));
}

void
__sst_ordered_array_resize (__sst_ordered_array_t *_sstoa)
{
  __sst_ordered_array_resize_to (_sstoa, (_sstoa->size + 1) << 1);
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

static void
__sst_ordered_array_place_cell (__sst_ordered_array_t *_sstoa,
                                __tableaux_cell_t      to_place,
                                __tableaux_cell_t *    replaced,
                                size_t                 pos,
                                size_t                 real_nr_replaced)
{
  if (_sstoa->counter == 0
      || to_place.val >= _sstoa->array[_sstoa->counter - 1].val)
  {
    if (_sstoa->counter + real_nr_to_place >= _sstoa->size)
    {
      __sst_ordered_array_resize_to (_sstoa,
                                     (_sstoa->size + real_nr_to_place) << 2);
    }
  }

  size_t missing = to_place.len;

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
  size_t idx = mid;
  if (_sstoa[idx].val == to_place.val)
  {
    _sstoa[idx].len += to_place.len;
    return;
  }
  
  while (missing > 0)
  {
    
  }
  *replaced          = _sstoa->array[mid];
  _sstoa->array[mid] = to_place[0];
  return nr_replaced;
}





void
__sst_ordered_array_place (__sst_ordered_array_t *_sstoa,
                           __tableaux_cell_t *    to_place,
                           size_t                 nr_to_place,
                           size_t                 real_nr_to_place,
                           __tableaux_cell_t *    replaced,
                           size_t                 nr_replaced,
                           size_t                 real_nr_replaced)
{
  size_t curr_replaced_pos = 0;
  size_t curr_to_place_pos = 0;
  size_t real_nr_placed    = 0;





  if (to_place[nr_to_place - 1].val >= _sstoa->array[_sstoa->counter - 1].val)
  {
    if (_sstoa->counter + real_nr_to_place >= _sstoa->size)
    {
      __sst_ordered_array_resize_to (_sstoa,
                                     (_sstoa->size + real_nr_to_place) << 1);
    }
  }



  size_t missing = to_place[curr_to_place_pos].len;

  while (nr put < nr to place)
  {
    missing_curr = x;
    while (missing_curr > 0)
    {
      place missing;
    }
  }

  size_t top    = _sstoa->counter - 1;
  size_t bottom = 0;
  size_t mid    = (top + bottom + 1) >> 1;


  while (true)
  {
    if (to_place[0].val < _sstoa->array[mid].val
        && (mid == 0 || to_place[0].val >= _sstoa->array[mid - 1].val))
    {
      break;
    }

    if (to_place[0].val < _sstoa->array[mid].val)
    {
      top = mid;
    } else
    {
      bottom = mid;
    }

    mid = (top + bottom + 1) >> 1;
  }

  *replaced          = _sstoa->array[mid];
  _sstoa->array[mid] = to_place[0];
  return nr_replaced;
}

#endif    // __SST_ORDERED_ARRAY__
