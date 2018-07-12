#include "semistandard_tableaux_word.h"

#ifdef __SST_TABLEAUX_WORD__

__sst_word_t *
__sst_tableaux_word_create (const __sst_t *_sst)
{
  size_t        sz    = __sst_tableaux_storage_size (_sst);
  __sst_word_t *_wsst = malloc (sizeof (__sst_word_t));
  _wsst->cells        = malloc (sz * sizeof (__tableaux_cell_t));
  _wsst->counter      = _wsst->size =
    __sst_tableaux_read_to_compressed_tableaux (_sst, _wsst->cells);
  return _wsst;
}

__sst_word_t *
__sst_tableaux_word_duplicate (const __sst_word_t *t)
{
  __sst_word_t *t_dup = malloc (sizeof (__sst_word_t));
  t_dup->size         = t->size;
  t_dup->counter      = t->counter;
  t_dup->cells        = malloc (t_dup->size * sizeof (__tableaux_cell_t));
  memcpy (t_dup->cells, t->cells, t->counter * sizeof (__tableaux_cell_t));
  return t_dup;
}

void
__sst_tableaux_word_destroy (__sst_word_t *_wsst)
{
  free (_wsst->cells);
  free (_wsst);
}

void
__sst_tableaux_word_resize_to (__sst_word_t *_wsst, const size_t sz)
{
  _wsst->size = sz >= _wsst->counter ? sz : _wsst->counter;
  _wsst->cells =
    realloc (_wsst->cells, _wsst->size * sizeof (__tableaux_cell_t));
}

void
__sst_tableaux_word_multiply (const __sst_word_t *_wsst_1,
                              const __sst_word_t *_wsst_2,
                              __sst_word_t *      _wsst_res)
{
  size_t req_sz = __sst_tableaux_word_storage_size (_wsst_1)
                  + __sst_tableaux_word_storage_size (_wsst_2);
  if (_wsst_res->size < req_sz)
  {
    __sst_tableaux_word_resize_to (
      _wsst_res,
      req_sz << 2);    // Just to leave some margin. And note that resizing to
                       // something twice as large ensures that if it continues
                       // growing, the number of resize operations will be low.
  }

  size_t counter = 0;
  for (size_t i = 0; i < _wsst_1->counter; i++, counter++)
  {
    _wsst_res->cells[counter].val = _wsst_1->cells[i].val;
    _wsst_res->cells[counter].len = _wsst_1->cells[i].len;
  }

  for (size_t i = 0; i < _wsst_2->counter; i++, counter++)
  {
    _wsst_res->cells[counter].val = _wsst_2->cells[i].val;
    _wsst_res->cells[counter].len = _wsst_2->cells[i].len;
  }
}

size_t
__sst_tableaux_word_size (const __sst_word_t *_wsst)
{
  size_t total_size = 0;
  for (size_t i = 0; i < _wsst->counter; i++)
  {
    total_size += _wsst->cells[i].len;
  }
  return total_size;
}

size_t
__sst_tableaux_word_storage_size (const __sst_word_t *_wsst)
{
  return _wsst->counter;
}

bool
__sst_tableaux_word_equals (const __sst_word_t *w1, const __sst_word_t *w2)
{
  __sst_t *l = __sst_tableaux_create ();
  __sst_t *r = __sst_tableaux_create ();

  __sst_tableaux_read_from_compressed_tableaux (l, w1->cells, w1->counter);
  __sst_tableaux_read_from_compressed_tableaux (r, w2->cells, w2->counter);

  bool ret = __sst_tableaux_equals (l, r);

  __sst_tableaux_destroy (l);
  __sst_tableaux_destroy (r);

  return ret;
}

bool
__sst_tableaux_word_check_identity (size_t *x,
                                    size_t  len_x,
                                    size_t *y,
                                    size_t  len_y,
                                    size_t *assigns,
                                    size_t  nr_vars,
                                    void *  elems)
{
  __sst_word_t **tableaux = (__sst_word_t **) elems;

  __sst_word_t left_side[len_x];
  __sst_word_t right_side[len_y];

  size_t len_left  = 0;
  size_t len_right = 0;

  for (size_t i = 0; i < len_x; i++)
  {
    __sst_word_t curr = *(tableaux[assigns[x[i]]]);
    left_side[i]      = curr;
    len_left          = len_left + curr.counter;
  }

  for (size_t i = 0; i < len_y; i++)
  {
    __sst_word_t curr = *(tableaux[assigns[y[i]]]);
    right_side[i]     = curr;
    len_right         = len_right + curr.counter;
  }

  __tableaux_cell_t left_cells[len_left];
  __tableaux_cell_t right_cells[len_right];

  __sst_word_t left = {
    .size = len_left, .counter = len_left, .cells = left_cells};

  __sst_word_t right = {
    .size = len_right, .counter = len_right, .cells = right_cells};

  for (size_t i = 0, j = 0; i < len_x; i++)
  {
    for (size_t k = 0; k < left_side[i].counter; k++)
    {
      left.cells[j].val   = left_side[i].cells[k].val;
      left.cells[j++].len = left_side[i].cells[k].len;
    }
  }

  for (size_t i = 0, j = 0; i < len_y; i++)
  {
    for (size_t k = 0; k < right_side[i].counter; k++)
    {
      right.cells[j].val   = right_side[i].cells[k].val;
      right.cells[j++].len = right_side[i].cells[k].len;
    }
  }

  return __sst_tableaux_word_equals (&left, &right);
}

// Different functions because of different types of return values
static __tableaux_cell_val_t
__sst_tableaux_word_get_max_val_tableaux (const __sst_word_t *_wsst)
{
  __tableaux_cell_val_t max = 0;
  for (size_t i = 0; i < _wsst->counter; i++)
  {
    __tableaux_cell_val_t v = _wsst->cells[i].val;
    max                     = max >= v ? max : v;
  }
  return max;
}

static __tableaux_cell_len_t
__sst_tableaux_word_get_max_len_tableaux (const __sst_word_t *_wsst)
{
  __tableaux_cell_len_t max = 0;
  for (size_t i = 0; i < _wsst->counter; i++)
  {
    __tableaux_cell_len_t v = _wsst->cells[i].len;
    max                     = max >= v ? max : v;
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

void
__sst_tableaux_word_print (const __sst_word_t *_wsst)
{
  size_t max_val_len = __sst_tableaux_get_val_len (
    __sst_tableaux_word_get_max_val_tableaux (_wsst));
  size_t max_len_len = __sst_tableaux_get_len_len (
    __sst_tableaux_word_get_max_len_tableaux (_wsst));
  for (size_t i = 0; i < _wsst->counter; i++)
  {
    printf ("(");
    __sst_tableaux_print_val (_wsst->cells[i].val, max_val_len, stdout);
    printf (",");
    __sst_tableaux_print_len (_wsst->cells[i].len, max_len_len, stdout);
    printf (") ");
  }
  printf ("\n");
}

void
__sst_tableaux_word_to_table_print (const __sst_word_t *_wsst)
{
  __sst_t *_sst = __sst_tableaux_table_create (_wsst);
  __sst_tableaux_print (_sst);
  __sst_tableaux_destroy (_sst);
}

void
__sst_tableaux_word_to_table_plain_print (const __sst_word_t *_wsst)
{
  __sst_t *_sst = __sst_tableaux_table_create (_wsst);
  __sst_tableaux_plain_print (_sst);
  __sst_tableaux_destroy (_sst);
}

void
__sst_tableaux_word_plain_print (const __sst_word_t *_wsst)
{
  size_t max_val_len = __sst_tableaux_get_val_len (
    __sst_tableaux_word_get_max_val_tableaux (_wsst));
  for (size_t i = 0; i < _wsst->counter; i++)
  {
    for (size_t j = 0; j < _wsst->cells[i].len; j++)
    {
      __sst_tableaux_print_val (_wsst->cells[i].val, max_val_len, stdout);
      printf (" ");
    }
  }
  printf ("\n");
}

__sst_word_t *
__sst_tableaux_word_read (const char *filename)
{
  char *        fn   = __utils_get_filename (filename, sst);
  __sst_t *     _sst = __sst_tableaux_read_plain_file (fn);
  __sst_word_t *res  = __sst_tableaux_word_create (_sst);
  __sst_tableaux_destroy (_sst);
  free (fn);
  return res;
}

void
__sst_tableaux_word_write (const __sst_word_t *_wsst, const char *filename)
{
  char *   fn = __utils_get_filename (filename, sst);
  __sst_t * _sst = __sst_tableaux_table_create (_wsst);
  __sst_tableaux_write_plain_file (_sst, fn);
  __sst_tableaux_destroy (_sst);
  free (fn);
}

#endif    // __SST_TABLEAUX_WORD__
