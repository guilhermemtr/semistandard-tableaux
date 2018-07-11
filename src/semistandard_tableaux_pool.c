#include "semistandard_tableaux_pool.h"

#ifdef __SST_POOL__

__sst_word_t *
__sst_pool_generate_random_tableaux (__tableaux_cell_val_t idx)
{
  return NULL;
}

__sst_pool_t *
__sst_pool_create_sst_pool ()
{
  __sst_pool_t *p = malloc (sizeof (__sst_pool_t));
  p->pool         = __ap_create_pool (
    (__ap_identity_tester *) __sst_tableaux_word_check_identity,
    (__ap_equals *) __sst_tableaux_word_equals,
    (__ap_op *) __sst_tableaux_word_destroy,
    (__ap_op *) __sst_tableaux_word_to_table_print);
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
  __ap_t *pool = p->pool;
  for (size_t i = 0; i < pool->counter; i++)
  {
    if (get_tableaux_index ((__sst_word_t *) (pool->pool_entries[i])) <= idx)
    {
      __sst_pool_add_word_tableaux (idx_p,
                                    __sst_tableaux_word_duplicate ((
                                      __sst_word_t *) (pool->pool_entries[i])));
    }
  }
  return idx_p;
}

void
__sst_pool_destroy_sst_pool (__sst_pool_t *p)
{
  __ap_destroy_pool (p->pool);
  free (p);
}

void
__sst_pool_add_word_tableaux (__sst_pool_t *p, __sst_word_t *t)
{
  __ap_add_element (p->pool, t);
}

bool
__sst_pool_test_identity (__sst_pool_t *      p,
                          char *              identity,
                          __va_assignment_t **counter_example)
{
  return __ap_test_identity (p->pool, identity, counter_example);
}

void
__sst_pool_add_tableaux_from_plain_file (__sst_pool_t *p, char *fn)
{
  __sst_t *t = __sst_tableaux_read_plain_file (fn);

  if (t == NULL)
  {
    return;
  }

  __sst_word_t *_wsst = __sst_tableaux_word_create (t);
  __sst_tableaux_destroy (t);
  __sst_pool_add_word_tableaux (p, _wsst);
}

void
__sst_pool_add_tableaux_from_compressed_file (__sst_pool_t *p, char *fn)
{
  __sst_t *     t     = __sst_tableaux_read_compressed_file (fn);
  __sst_word_t *_wsst = __sst_tableaux_word_create (t);

  if (t == NULL)
  {
    return;
  }

  __sst_tableaux_destroy (t);
  __sst_pool_add_word_tableaux (p, _wsst);
}

void
__sst_pool_add_tableaux_from_table_file (__sst_pool_t *p, char *fn)
{
  __sst_t *t = __sst_tableaux_read_table_file (fn);

  if (t == NULL)
  {
    return;
  }

  __sst_word_t *_wsst = __sst_tableaux_word_create (t);
  __sst_tableaux_destroy (t);
  __sst_pool_add_word_tableaux (p, _wsst);
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
      } else if (str_suffix_match (ent->d_name, ".sstt"))
      {
        size_t fn_len = strlen (ent->d_name);
        char   concat[len_dir_path + fn_len + 1];
        strcpy (concat, dir_path);
        strcpy (&(concat[len_dir_path]), ent->d_name);
        __sst_pool_add_tableaux_from_table_file (p, concat);
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
  __ap_remove_duplicates (p->pool);
}

void
__sst_pool_print (__sst_pool_t *p)
{
  __ap_print (p->pool);
}

void
__sst_pool_custom_print (__sst_pool_t *p, void (*print) (const __sst_word_t *))
{
  __ap_t *pool = p->pool;
  for (size_t i = 0; i < pool->counter; i++)
  {
    (*print) ((__sst_word_t *) (pool->pool_entries[i]));
  }
}

#endif    // __SST_POOL__
