#include "semistandard_tableaux_pool.h"

#ifdef __SST_POOL__

__sst_t *
__sst_pool_generate_random_tableaux (__tableaux_cell_val_t idx)
{
  return NULL;
}

static void
__sst_pool_resize_to (__sst_pool_t *p, size_t sz)
{
  p->size = sz >= p->counter ? sz : p->counter;
  p->tableaux =
    (__sst_t **) realloc (p->tableaux, p->size * sizeof (__sst_t *));
}

__sst_pool_t *
__sst_pool_create_sst_pool ()
{
  __sst_pool_t *p = malloc (sizeof (__sst_pool_t));
  p->size         = __SST_POOL_DEFAULT_SIZE;
  p->counter      = 0;
  p->tableaux     = (__sst_t **) malloc (p->size * sizeof (__sst_t *));
  return p;
}

static __tableaux_cell_val_t
get_tableaux_index (__sst_t *_sst)
{
  __tableaux_cell_val_t max = 0;
  for (size_t i = 0; i < _sst->counter; i++)
  {
    for (size_t j = 0; j < _sst->rows[i].counter; j++)
    {
      __tableaux_cell_val_t v = _sst->rows[i].array[j].val;
      max                     = max >= v ? max : v;
    }
  }
  return max;
}

__sst_pool_t *
__sst_pool_create_sst__index_pool (__sst_pool_t *p, __tableaux_cell_val_t idx)
{
  __sst_pool_t *idx_p = __sst_pool_create_sst_pool ();
  __sst_pool_remove_duplicates (p);

  for (size_t i = 0; i < p->counter; i++)
  {
    if (get_tableaux_index (p->tableaux[i]) <= idx)
    {
      __sst_pool_add_tableaux (idx_p,
                               __sst_tableaux_duplicate (p->tableaux[i]));
    }
  }
  return idx_p;
}

void
__sst_pool_destroy_sst_pool (__sst_pool_t *p)
{
  for (size_t i = 0; i < p->counter; i++)
  {
    __sst_tableaux_destroy (p->tableaux[i]);
  }
  free (p->tableaux);
  free (p);
}

void
__sst_pool_add_tableaux (__sst_pool_t *p, __sst_t *t)
{
  if (p->counter == p->size)
  {
    __sst_pool_resize_to (p, (p->size + 1) << 1);
  }
  p->tableaux[p->counter++] = t;
}

void
__sst_pool_add_tableaux_from_plain_file (__sst_pool_t *p, char *fn)
{
  __sst_t *t = __sst_tableaux_read_plain_file (fn);
  __sst_pool_add_tableaux (p, t);
}

void
__sst_pool_add_tableaux_from_compressed_file (__sst_pool_t *p, char *fn)
{
  __sst_t *t = __sst_tableaux_read_compressed_file (fn);
  __sst_pool_add_tableaux (p, t);
}

void
__sst_pool_add_random_tableaux (__sst_pool_t *        p,
                                size_t                nr_random,
                                __tableaux_cell_val_t idx)
{
  for (size_t i = 0; i < nr_random; i++)
  {
    __sst_pool_add_tableaux (p, __sst_pool_generate_random_tableaux (idx));
  }
}

void
__sst_pool_remove_duplicates (__sst_pool_t *p)
{
  for (size_t i = 0; i < p->counter; i++)
  {
    if (p->tableaux[i] == NULL)
    {
      continue;
    }

    for (size_t j = i + 1; j < p->counter; j++)
    {
      if (p->tableaux[j] == NULL)
      {
        continue;
      }

      if (__sst_tableaux_equals (p->tableaux[i], p->tableaux[j]))
      {
        __sst_tableaux_destroy (p->tableaux[j]);
        p->tableaux[j] = NULL;
      }
    }
  }

  size_t ctr = p->counter;
  for (size_t i = 0; i < ctr; i++)
  {
    if (p->tableaux[i] == NULL)
    {
      while (p->tableaux[--ctr] == NULL && i < ctr)
      {
        ;
      }
      p->tableaux[i] = p->tableaux[ctr];
    }
  }
  p->counter = ctr;
}

void
__sst_pool_print (__sst_pool_t *p, void (*print) (const __sst_t *))
{
  printf ("Showing entries of tableaux pool %p\n", p);

  for (size_t i = 0; i < p->counter; i++)
  {
    printf ("Entry %lu:\n", i);
    print (p->tableaux[i]);
    printf ("\n");
  }
}


#endif    // __SST_POOL__
