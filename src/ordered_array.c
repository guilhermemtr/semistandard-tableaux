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
__sst_ordered_array_duplicate (__sst_ordered_array_t *_sstoa_from,
                               __sst_ordered_array_t *_sstoa_to)
{
  _sstoa_to->size  = _sstoa_from->size;
  _sstoa_to->array = malloc (_sstoa_to->size * sizeof (__tableaux_cell_t));
  __sst_ordered_array_copy (_sstoa_from, _sstoa_to);
}

void
__sst_ordered_array_destroy (__sst_ordered_array_t *_sstoa)
{
  _sstoa->size = _sstoa->counter = 0;
  free (_sstoa->array);
}

size_t
__sst_ordered_array_size (__sst_ordered_array_t *_sstoa)
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

static size_t
get_mid (__sst_ordered_array_t *_sstoa, __tableaux_cell_val_t val)
{
  size_t top    = _sstoa->counter - 1;
  size_t bottom = 0;
  size_t mid    = (top + bottom) >> 1;

  while (true)
  {
    if (val < _sstoa->array[mid].val
        && (mid == 0 || val >= _sstoa->array[mid - 1].val))
    {
      break;
    }

    if (val >= _sstoa->array[mid].val)
    {
      bottom = mid + 1;
    } else
    {
      top = mid;
    }

    mid = (top + bottom) >> 1;
  }
  return mid;
}

static void
place_cell_mid (__sst_ordered_array_t *_sstoa,
                size_t *               idx,
                __tableaux_cell_t      to_place)
{
  if (*idx == 0 || _sstoa->array[*idx - 1].val < to_place.val)
  {
    if (_sstoa->counter == _sstoa->size)
    {
      __sst_ordered_array_resize_to (_sstoa,
                                     (_sstoa->size + to_place.len) << 2);
    }

    for (size_t i = _sstoa->counter; i > *idx; i--)
    {
      _sstoa->array[i] = _sstoa->array[i - 1];
    }

    _sstoa->array[*idx] = to_place;
    _sstoa->counter++;
    *idx = *idx + 1;
  } else    // _sstoa->array[*idx - 1].val == to_place.val
  {
    _sstoa->array[*idx - 1].len += to_place.len;
  }
}

static void
shift_cells_after_mid (__sst_ordered_array_t *_sstoa,
                       size_t *               idx,
                       __tableaux_cell_len_t  extra,
                       __tableaux_cell_t *    replaced,
                       size_t *               pos)
{
  size_t beg = 0;
  size_t dis = 0;

  while (extra > 0)
  {
    if (*idx >= _sstoa->counter)
    {
      extra = 0;
    } else if (extra >= _sstoa->array[*idx].len)
    {
      if (dis == 0)
      {
        beg = *idx;
        dis = 1;
      } else
      {
        dis++;
      }
      replaced[*pos] = _sstoa->array[*idx];
      *pos           = *pos + _sstoa->array[*idx].len;
      extra          = extra - _sstoa->array[*idx].len;
    } else    // extra < _sstoa[*idx].len
    {
      replaced[*pos]          = _sstoa->array[*idx];
      replaced[*pos].len      = extra;
      _sstoa->array[*idx].len = _sstoa->array[*idx].len - extra;
      *pos                    = *pos + extra;
      extra                   = 0;
    }
    *idx = *idx + 1;
  }

  // shift all one to the left
  for (size_t i = beg; i + dis < _sstoa->counter; i++)
  {
    _sstoa->array[i] = _sstoa->array[i + dis];
  }
  _sstoa->counter -= dis;
}

static void
place_cell (__sst_ordered_array_t *_sstoa,
            __tableaux_cell_t      to_place,
            __tableaux_cell_t *    replaced,
            size_t *               pos)
{
  // if the cell is to be appended
  if (_sstoa->counter == 0
      || to_place.val >= _sstoa->array[_sstoa->counter - 1].val)
  {
    if (_sstoa->counter == _sstoa->size)
    {
      __sst_ordered_array_resize_to (_sstoa,
                                     (_sstoa->size + to_place.len) << 2);
    }

    if ((_sstoa->counter == 0)
        || (to_place.val > _sstoa->array[_sstoa->counter - 1].val))
    {
      _sstoa->array[_sstoa->counter++] = to_place;
    } else    // _sstoa->array[_sstoa->counter - 1].val == to_place.val
    {
      _sstoa->array[_sstoa->counter - 1].len += to_place.len;
    }
    return;
  }

  // if the cell is not to be appended
  // search for correct position to place the cell
  size_t idx = get_mid (_sstoa, to_place.val);

  // place the cell
  place_cell_mid (_sstoa, &idx, to_place);

  // remove all the extra cells, starting at idx (to append them to another row)
  shift_cells_after_mid (_sstoa, &idx, to_place.len, replaced, pos);
}

void
__sst_ordered_array_place (__sst_ordered_array_t *_sstoa,
                           __tableaux_cell_t *    to_place,
                           size_t                 real_nr_to_place,
                           __tableaux_cell_t *    replaced,
                           size_t *               real_nr_replaced)
{
  size_t nr_placed  = 0;
  *real_nr_replaced = 0;

  // add the cells, one by one
  while (nr_placed < real_nr_to_place)
  {
    place_cell (_sstoa, to_place[nr_placed], replaced, real_nr_replaced);
    nr_placed += to_place[nr_placed].len;
  }
}

void
print_array (__sst_ordered_array_t *_sstoa)
{
  printf ("[");
  for (size_t i = 0; i < _sstoa->counter; i++)
  {
    printf ("{%lu, %lu},\t", _sstoa->array[i].val, _sstoa->array[i].len);
  }
  printf ("]\n");
}

#endif    // __SST_ORDERED_ARRAY__
