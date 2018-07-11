#include "tropical_matrices_pool.h"

#ifdef __TM_POOL__

__tm_pool_t *
__tm_pool_create_tm_pool ()
{
  __tm_pool_t *p = malloc (sizeof (__tm_pool_t));
  p->pool        = __ap_create_pool (
    NULL, NULL, NULL, NULL); /*__sst_tableaux_word_check_identity,
                     __sst_tableaux_word_equals,
                     __sst_tableaux_word_destroy,
                     __sst_tableaux_word_to_table_print);*/
  return p;
}

void
__tm_pool_destroy_tm_pool (__tm_pool_t *p)
{
  __ap_destroy_pool (p->pool);
  free (p);
}

void
__tm_pool_add_tropical_matrix (__tm_pool_t *p, __tm_t *t)
{
  __ap_add_element (p->pool, t);
}

bool
__tm_pool_test_identity (__tm_pool_t *       p,
                         char *              identity,
                         __va_assignment_t **counter_example)
{
  return __ap_test_identity (p->pool, identity, counter_example);
}

void
__tm_pool_add_matrix_from_plain_file (__tm_pool_t *p, char *fn)
{
  __tm_t *t = __tm_read (fn);

  if (t == NULL)
  {
    return;
  }

  __tm_pool_add_tropical_matrix (p, t);
}

void
__tm_pool_add_tableaux_from_directory (__tm_pool_t *p, char *dir_path)
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
      size_t fn_len = strlen (ent->d_name);
      char   concat[len_dir_path + fn_len + 1];
      strcpy (concat, dir_path);
      strcpy (&(concat[len_dir_path]), ent->d_name);

      if (str_suffix_match (ent->d_name, ".tm"))
      {
        __tm_pool_add_matrix_from_plain_file (p, concat);
      }
    }
    closedir (dir);
  }
}

void
__tm_pool_remove_duplicates (__tm_pool_t *p)
{
  __ap_remove_duplicates (p->pool);
}

void
__tm_pool_print (__tm_pool_t *p)
{
  __ap_print (p->pool);
}

void
__tm_pool_custom_print (__tm_pool_t *p, void (*print) (const __tm_t *))
{
  __ap_t *pool = p->pool;
  for (size_t i = 0; i < pool->counter; i++)
  {
    (*print) ((__tm_t *) (pool->pool_entries[i]));
  }
}

#endif    // __TM_POOL__
