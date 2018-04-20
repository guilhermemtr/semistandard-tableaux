#include "semistandard_tableaux_pool.h"

#ifdef __SST_POOL__

__sst_word_t *
__sst_pool_generate_random_tableaux (__tableaux_cell_val_t idx)
{
  return NULL;
}

static void
__sst_pool_resize_to (__sst_pool_t *p, size_t sz)
{
  p->size = sz >= p->counter ? sz : p->counter;
  p->tableaux =
    (__sst_word_t **) realloc (p->tableaux, p->size * sizeof (__sst_word_t *));
}

__sst_pool_t *
__sst_pool_create_sst_pool ()
{
  __sst_pool_t *p = malloc (sizeof (__sst_pool_t));
  p->size         = __SST_POOL_DEFAULT_SIZE;
  p->counter      = 0;
  p->tableaux = (__sst_word_t **) malloc (p->size * sizeof (__sst_word_t *));
  return p;
}

static __tableaux_cell_val_t
get_tableaux_index (__sst_word_t *_wsst)
{
  __tableaux_cell_val_t max = 0;
  for (size_t i = 0; i < _wsst->counter; i++)
  {
    __tableaux_cell_val_t v = _wsst->cells[i].val;
    max                     = max >= v ? max : v;
  }
  return max;
}

__sst_pool_t *
__sst_pool_create_sst_index_pool (__sst_pool_t *p, __tableaux_cell_val_t idx)
{
  __sst_pool_t *idx_p = __sst_pool_create_sst_pool ();
  __sst_pool_remove_duplicates (p);

  for (size_t i = 0; i < p->counter; i++)
  {
    if (get_tableaux_index (p->tableaux[i]) <= idx)
    {
      __sst_pool_add_word_tableaux (
        idx_p, __sst_tableaux_word_duplicate (p->tableaux[i]));
    }
  }
  return idx_p;
}

void
__sst_pool_destroy_sst_pool (__sst_pool_t *p)
{
  for (size_t i = 0; i < p->counter; i++)
  {
    __sst_tableaux_word_destroy (p->tableaux[i]);
  }
  free (p->tableaux);
  free (p);
}

void
__sst_pool_add_word_tableaux (__sst_pool_t *p, __sst_word_t *t)
{
  if (p->counter == p->size)
  {
    __sst_pool_resize_to (p, (p->size + 1) << 1);
  }
  p->tableaux[p->counter++] = t;
}

bool
__sst_pool_test_identity (__sst_pool_t *      p,
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
__sst_pool_add_tableaux_from_plain_file (__sst_pool_t *p, char *fn)
{
  __sst_t *     t     = __sst_tableaux_read_plain_file (fn);
  __sst_word_t *_wsst = __sst_tableaux_word_create (t);
  __sst_tableaux_destroy (t);
  __sst_pool_add_word_tableaux (p, _wsst);
}

void
__sst_pool_add_tableaux_from_compressed_file (__sst_pool_t *p, char *fn)
{
  __sst_t *     t     = __sst_tableaux_read_compressed_file (fn);
  __sst_word_t *_wsst = __sst_tableaux_word_create (t);
  __sst_tableaux_destroy (t);
  __sst_pool_add_word_tableaux (p, _wsst);
}

// copied from
// https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
static bool
str_suffix_match (const char *str, const char *suffix)
{
  if (str == NULL || suffix == NULL)
  {
    return 0;
  }

  size_t lenstr    = strlen (str);
  size_t lensuffix = strlen (suffix);

  if (lensuffix > lenstr)
  {
    return 0;
  }

  return strncmp (str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

void
__sst_pool_add_tableaux_from_directory (__sst_pool_t *p, char *dir_path)
{
  DIR *          dir;
  struct dirent *ent;
  dir = opendir (dir_path);

  if (dir != NULL)
  {
    size_t len_dir_path = strlen (dir_path);
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL)
    {
      if (str_suffix_match (ent->d_name, ".sst"))
      {
        size_t fn_len = strlen (ent->d_name);
        char   concat[len_dir_path + fn_len + 1];
        strcpy (concat, dir_path);
        strcpy (&(concat[len_dir_path]), ent->d_name);
        __sst_pool_add_tableaux_from_plain_file (p, concat);
      } else if (str_suffix_match (ent->d_name, ".sstc"))
      {
        size_t fn_len = strlen (ent->d_name);
        char   concat[len_dir_path + fn_len + 1];
        strcpy (concat, dir_path);
        strcpy (&(concat[len_dir_path]), ent->d_name);
        __sst_pool_add_tableaux_from_compressed_file (p, concat);
      }
    }
    closedir (dir);
  }
}

void
__sst_pool_add_random_tableaux (__sst_pool_t *        p,
                                size_t                nr_random,
                                __tableaux_cell_val_t idx)
{
  for (size_t i = 0; i < nr_random; i++)
  {
    __sst_pool_add_word_tableaux (p, __sst_pool_generate_random_tableaux (idx));
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

      __sst_t *l = __sst_tableaux_table_create (p->tableaux[i]);
      __sst_t *r = __sst_tableaux_table_create (p->tableaux[j]);

      if (__sst_tableaux_equals (l, r))
      {
        __sst_tableaux_word_destroy (p->tableaux[j]);
        p->tableaux[j] = NULL;
      }

      __sst_tableaux_destroy (l);
      __sst_tableaux_destroy (r);
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
__sst_pool_print (__sst_pool_t *p, void (*print) (const __sst_word_t *))
{
  printf ("Showing entries of tableaux pool %p\n", p);

  for (size_t i = 0; i < p->counter; i++)
  {
    printf ("Entry %lu:\tSize:%lu\n", i, p->tableaux[i]->counter);
    print (p->tableaux[i]);
    printf ("\n");
  }
}


#endif    // __SST_POOL__
