#include "tropical_matrix.h"

#ifdef __TROPICAL_MATRICES__

__tm_t *
__tm_create (size_t columns, size_t rows)
{
  __tm_t *m  = malloc (sizeof (__tm_t));
  m->columns = columns;
  m->rows    = rows;
  m->matrix  = malloc (m->columns * m->rows * sizeof (__tn_t));
  for (size_t i = 0; i < m->columns * m->rows; i++)
  {
    m->matrix[i] = __tn_neg_inf;
  }
  return m;
}

void
__tm_destroy (__tm_t *_tm)
{
  free (_tm->matrix);
  free (_tm);
}

void
__tm_sum (__tm_t *m1, __tm_t *m2, __tm_t *res)
{
  for (size_t i = 0; i < m1->rows * m1->columns; i++)
  {
    res->matrix[i] = __tn_sum (m1->matrix[i], m2->matrix[i]);
  }
}


void
__tm_mult (__tm_t *m1, __tm_t *m2, __tm_t *res)
{
  for (size_t i = 0; i < res->columns; i++)
  {
    for (size_t j = 0; j < res->rows; j++)
    {
      res->matrix[i + j * res->columns] = __tn_neg_inf;
      for (size_t k = 0; k < m1->columns; k++)
      {
        res->matrix[i + j * res->columns] =
          __tn_sum (res->matrix[i + j * res->columns],
                    __tn_mult (m1->matrix[k + j * m1->rows],
                               m2->matrix[i + k * m2->rows]));
      }
    }
  }
}

bool
__tm_check_identity (size_t *x,
                     size_t  len_x,
                     size_t *y,
                     size_t  len_y,
                     size_t *assigns,
                     size_t  nr_vars,
                     void *  elems)
{
  /*__tm_t **matrices = (__tm_t **) elems;

  __tm_t left_side[len_x];
  __tm_t right_side[len_y];

  size_t len_left  = 0;
  size_t len_right = 0;

  for (size_t i = 0; i < len_x; i++)
  {
    __tm_t curr  = *(matrices[assigns[x[i]]]);
    left_side[i] = curr;
    len_left     = len_left + curr.counter;
  }

  for (size_t i = 0; i < len_y; i++)
  {
    __tm_t curr   = *(tableaux[assigns[y[i]]]);
    right_side[i] = curr;
    len_right     = len_right + curr.counter;
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

  return __sst_tableaux_word_equals (&left, &right);*/
  return false;
}

__tm_t *
__tm_read (char *filename)
{
  FILE *f = fopen (filename, "r");

  if (f == NULL)
  {
    return NULL;
  }

  ssize_t read;
  char *  line     = NULL;
  size_t  len      = 0;
  char *  save_ptr = NULL;

  size_t  sz      = 32L;
  __tn_t *tns     = malloc (sz * sizeof (__tn_t));
  size_t  entries = 0;
  size_t  rows    = 0;


  while ((read = getline (&line, &len, f)) != -1)
  {
    char *tmp = line;
    char *res;
    while ((res = strtok_r (tmp, " ", &save_ptr)) != NULL)
    {
      tmp = NULL;

      if (entries == sz)
      {
        sz  = sz * 2;
        tns = realloc (tns, sz * sizeof (__tn_t));
      }

      __tn_t tn;
      if (strcmp ("-inf", res) == 0)
      {
        tn = __tn_neg_inf;
      } else
      {
        if (sscanf (res, "%lu", &tn) < 0)
        {
          // failed reading an entry.
          free (tns);
          return NULL;
        }
      }
      tns[entries++] = tn;
    }

    free (line);
    line = NULL;
    rows++;
  }

  fclose (f);
  __tm_t *tm  = malloc (sizeof (__tm_t));
  tm->matrix  = tns;
  tm->rows    = rows;
  tm->columns = entries / rows;
  return tm;
}

static void
__tn_write (__tn_t n, FILE *f)
{
  printf ("%lu \n", n);
  if (__tn_is_infinite (n))
  {
    fprintf (f, "-inf ");
  } else
  {
    fprintf (f, "%lu ", __tn_get_value (n));
  }
}

static void
__tm_write_file (__tm_t *m, FILE *f)
{
  if (f == NULL)
  {
    return;
  }

  for (size_t i = 0; i < m->rows; i++)
  {
    for (size_t j = 0; j < m->columns; j++)
    {
      __tn_write (m->matrix[i * m->columns + j], f);
    }
    fprintf (f, "\n");
  }
}

void
__tm_write (__tm_t *m, char *filename)
{
  FILE *f = fopen (filename, "w");

  __tm_write_file (m, f);
  fclose (f);
}

void
__tm_print (__tm_t *m)
{
  __tm_write_file (m, stdout);
}

#endif    // __TROPICAL_MATRICES__
