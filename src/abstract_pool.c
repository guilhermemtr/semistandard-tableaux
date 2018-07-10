#include "abstract_pool.h"

#ifdef __ABSTRACT_POOL__

static void
__abstract_pool_resize_to (__abstract_pool_t *p, size_t sz)
{
  p->size     = sz >= p->counter ? sz : p->counter;
  p->tableaux = (__sst_word_t **) realloc (p->pool_entries, p->size);
}


__abstract_pool_t *
__abstract_pool_create_pool ()
{
  __abstract_pool_t *p = malloc (sizeof (__abstract_pool_t));
  p->size              = __ABSTRACT_POOL_DEFAULT_SIZE;
  p->counter           = 0;
  p->pool_entries      = (void **) malloc (p->size * sizeof (void *));
  return p;
}

void
__abstract_pool_destroy_pool (__abstract_pool_t *p,
                              void (*entry_destroy) (void *))
{
  for (size_t i = 0; i < p->counter; i++)
  {
    __sst_tableaux_word_destroy (p->tableaux[i]);
  }
  free (p->tableaux);
  free (p);
}


void
__abstract_pool_add_element (__abstract_pool_t *p, void *e)
{
  if (p->counter == p->size)
  {
    __sst_pool_resize_to (p, (p->size + 1) << 1);
  }
  p->tableaux[p->counter++] = t;
}


bool
__abstract_pool_test_identity (__abstract_pool_t * p,
                               char *              identity,
                               __it_assignment_t **counter_example)
{
  return __it_test_identity (identity,
                             p->tableaux,
                             p->counter,
                             __sst_tableaux_check_identity,
                             counter_example);
}

void
__abstract_pool_remove_duplicates (__abstract_pool_t *p);

void
__abstract_pool_print (__abstract_pool_t *p, void (*print) (void *))
{
  printf ("Showing entries of tableaux pool %p\n", p);

  for (size_t i = 0; i < p->counter; i++)
  {
    printf ("Entry %lu:\tSize:%lu\n", i, p->tableaux[i]->counter);
    print (p->tableaux[i]);
    printf ("\n");
  }
}

#endif    // __ABSTRACT_POOL__
