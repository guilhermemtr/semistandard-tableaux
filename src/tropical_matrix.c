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

__tm_t *
__tm_duplicate (__tm_t *m)
{
  __tm_t *clone  = malloc (sizeof (__tm_t));
  clone->columns = m->columns;
  clone->rows    = m->rows;
  clone->matrix  = malloc (clone->columns * clone->rows * sizeof (__tn_t));
  for (size_t i = 0; i < clone->columns * clone->rows; i++)
  {
    clone->matrix[i] = m->matrix[i];
  }
  return clone;
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
__tm_equals (__tm_t *l, __tm_t *r)
{
  if (l->rows != r->rows || l->columns != r->columns)
  {
    return false;
  }

  for (size_t i = 0; i < l->rows * l->columns; i++)
  {
    if (!__tn_equals (l->matrix[i], r->matrix[i]))
    {
      return false;
    }
  }

  return true;
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
  __tm_t **matrices = (__tm_t **) elems;
  // It is assumed that all the given matrices are of the same size
  size_t  cols      = matrices[0]->columns;
  size_t  rows      = matrices[0]->rows;
  __tm_t *left_curr = __tm_duplicate (matrices[assigns[x[0]]]);
  __tm_t *left_res  = __tm_create (cols, rows);

  __tm_t *right_curr = __tm_duplicate (matrices[assigns[y[0]]]);
  __tm_t *right_res  = __tm_create (cols, rows);

  for (size_t i = 1; i < len_x; i++)
  {
    __tm_mult (left_curr, matrices[assigns[x[i]]], left_res);
    __tm_t *tmp = left_res;
    left_res    = left_curr;
    left_curr   = tmp;
  }

  for (size_t i = 1; i < len_y; i++)
  {
    __tm_mult (right_curr, matrices[assigns[y[i]]], right_res);
    __tm_t *tmp = right_res;
    right_res   = right_curr;
    right_curr  = tmp;
  }

  bool identity_checks = __tm_equals (left_res, right_res);

  __tm_destroy (left_curr);
  __tm_destroy (left_res);
  __tm_destroy (right_curr);
  __tm_destroy (right_res);

  return identity_checks;
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
