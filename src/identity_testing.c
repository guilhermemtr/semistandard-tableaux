#include "identity_testing.h"

#ifdef __IDENTITY_TESTING__


/* Function that trims the given string.
 */
static void
trim (char *str)
{
  size_t b = 0;
  size_t c = 0;
  while (str[c] != '\0')
  {
    if (!isspace (str[c]))
    {
      str[b++] = str[c];
    }
    c++;
  }
  str[b] = '\0';
}


static void
split_identity (char *identity, char **split1, char **split2)
{
  char *save_ptr;
  *split1 = strtok_r (identity, __IT_DELIMITER__, &save_ptr);
  *split2 = strtok_r (NULL, __IT_DELIMITER__, &save_ptr);
}

static void
split_identity_variables (char *side, char **splits, size_t *nr_splits)
{
  char *save_ptr;
  *nr_splits = 0;
  while ((splits[*nr_splits] = strtok_r (side, __IT_OP_SYMBOL__, &save_ptr))
         != NULL)
  {
    *nr_splits = *nr_splits + 1;
    side       = NULL;
  }
}


// TODO optimize for different sizes (specially smaller sizes)
static size_t
get_mapped_splits (char ** splits_1,
                   size_t  nr_splits_1,
                   char ** splits_2,
                   size_t  nr_splits_2,
                   size_t *mapped_splits_1,
                   size_t *mapped_splits_2)
{
  // create the mappings
  map_t  mappings = hashmap_new ();
  size_t id       = 0;
  any_t  tmp;

  for (size_t i = 0; i < nr_splits_1; i++)
  {
    if (hashmap_get (mappings, splits_1[i], &tmp) == MAP_MISSING)
    {
      hashmap_put (mappings, splits_1[i], (void *) id);
      id++;
    }
  }

  for (size_t i = 0; i < nr_splits_2; i++)
  {
    if (hashmap_get (mappings, splits_2[i], &tmp) == MAP_MISSING)
    {
      hashmap_put (mappings, splits_2[i], (void *) id);
      id++;
    }
  }

  // substitute the mappings
  for (size_t i = 0; i < nr_splits_1; i++)
  {
    assert (hashmap_get (mappings, splits_1[i], &tmp) == MAP_OK);
    mapped_splits_1[i] = (size_t) tmp;
  }

  for (size_t i = 0; i < nr_splits_2; i++)
  {
    assert (hashmap_get (mappings, splits_2[i], &tmp) == MAP_OK);
    mapped_splits_2[i] = (size_t) tmp;
  }
  return id;
}

bool
__it_test_identity (char *           identity,
                    void *           elems,
                    size_t           nr_elems,
                    identity_testing fn)    // TODO
{
  trim (identity);

  char *split_1;
  char *split_2;

  split_identity (identity, &split_1, &split_2);

  size_t split_1_sz = strlen (split_1);
  size_t split_2_sz = strlen (split_2);

  char *splits_1[split_1_sz];
  char *splits_2[split_2_sz];

  size_t nr_splits_1 = 0;
  size_t nr_splits_2 = 0;

  split_identity_variables (split_1, splits_1, &nr_splits_1);
  split_identity_variables (split_2, splits_2, &nr_splits_2);

  size_t mapped_splits_1[nr_splits_1];
  size_t mapped_splits_2[nr_splits_2];

  size_t nr_vars = get_mapped_splits (splits_1,
                                      nr_splits_1,
                                      splits_2,
                                      nr_splits_2,
                                      mapped_splits_1,
                                      mapped_splits_2);


  bool test_identity (size_t beg, size_t * id)
  {
    if (beg == nr_vars)
    {
      return fn (mapped_splits_1,
                 nr_splits_1,
                 mapped_splits_2,
                 nr_splits_2,
                 id,
                 nr_vars,
                 elems);
    } else
    {
      size_t tests[nr_elems][beg + 1];
      bool   oks[nr_elems];
      for (size_t i = 0; i < nr_elems; i++)
      {
        oks[i] = true;
        for (size_t j = 0; j < beg; j++)
        {
          tests[i][j] = id[j];
        }
      }
      for (size_t i = 0; i < nr_elems; i++)
      {
        tests[i][beg] = i;
        oks[i]        = spawn (test_identity (beg + 1, tests[i]));
      }
      sync;
      bool ok = true;
      for (size_t i = 0; i < nr_elems; i++)
      {
        ok &= oks[i];
      }
      return ok;
    }
  }

  return test_identity (0, NULL);
}

#endif    // __IDENTITY_TESTING__
