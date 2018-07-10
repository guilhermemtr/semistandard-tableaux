#include "abstract_pool.h"

#ifdef __ABSTRACT_POOL__

static void
__ap_resize_to (__ap_t *p, size_t sz)
{
  p->size         = sz >= p->counter ? sz : p->counter;
  p->pool_entries = (void **) realloc (p->pool_entries, p->size);
}


__ap_t *
__ap_create_pool ()
{
  __ap_t *p       = malloc (sizeof (__ap_t));
  p->size         = __AP_DEFAULT_SIZE;
  p->counter      = 0;
  p->pool_entries = (void **) malloc (p->size * sizeof (void *));
  return p;
}

void
__ap_destroy_pool (__ap_t *p)
{
  for (size_t i = 0; i < p->counter; i++)
  {
    (*p->destroy) (p->pool_entries[i]);
  }
  free (p->pool_entries);
  free (p);
}

void
__ap_add_element (__ap_t *p, void *e)
{
  if (p->counter == p->size)
  {
    __ap_resize_to (p, (p->size + 1) << 1);
  }
  p->pool_entries[p->counter++] = e;
}

static bool
test_identity (char *               identity,
               void *               elems,
               size_t               nr_elems,
               __ap_identity_tester fn,
               __va_assignment_t ** counter_example);

bool
__ap_test_identity (__ap_t *            p,
                    char *              identity,
                    __va_assignment_t **counter_example)
{
  return test_identity (
    identity, p->pool_entries, p->counter, p->tester, counter_example);
}

void
__ap_remove_duplicates (__ap_t *p)
{
  for (size_t i = 0; i < p->counter; i++)
  {
    if (p->pool_entries[i] == NULL)
    {
      continue;
    }

    for (size_t j = i + 1; j < p->counter; j++)
    {
      if (p->pool_entries[j] == NULL)
      {
        continue;
      }

      if ((*p->equals) (p->pool_entries[i], p->pool_entries[j]))
      {
        (*p->destroy) (p->pool_entries[j]);
        p->pool_entries[j] = NULL;
      }
    }
  }

  size_t ctr = p->counter;
  for (size_t i = 0; i < ctr; i++)
  {
    if (p->pool_entries[i] == NULL)
    {
      while (p->pool_entries[--ctr] == NULL && i < ctr)
      {
        ;
      }
      p->pool_entries[i] = p->pool_entries[ctr];
    }
  }
  p->counter = ctr;
}

void
__ap_print (__ap_t *p)
{
  printf ("Showing entries of tableaux pool %p\n", p);

  for (size_t i = 0; i < p->counter; i++)
  {
    printf ("Entry %lu\n", i);
    (*p->print) (p->pool_entries[i]);
    printf ("\n");
  }
}



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
  *split1 = strtok_r (identity, __AP_DELIMITER__, &save_ptr);
  *split2 = strtok_r (NULL, __AP_DELIMITER__, &save_ptr);
}

static void
split_identity_variables (char *side, char **splits, size_t *nr_splits)
{
  char *save_ptr;
  *nr_splits = 0;
  while ((splits[*nr_splits] = strtok_r (side, __AP_OP_SYMBOL__, &save_ptr))
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
                   size_t *mapped_splits_2,
                   char ** vars)
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
    if (vars != NULL)
    {
      vars[(size_t) tmp] = splits_1[i];
    }
  }

  for (size_t i = 0; i < nr_splits_2; i++)
  {
    assert (hashmap_get (mappings, splits_2[i], &tmp) == MAP_OK);
    mapped_splits_2[i] = (size_t) tmp;
    if (vars != NULL)
    {
      vars[(size_t) tmp] = splits_2[i];
    }
  }
  return id;
}

/** Tests the validity of the given identity.
 * Tests the validity of the given identity, by trying all possible combinations
 * of the given elements, and verifying if the identity holds for those
 * combinations.
 * @param identity the identity to be verified, a string of the form
 * "a1.a2...=b1.b2...".
 * @param elems the elements to which the variables can be set.
 * @param nr_elems the number of elements to which the variables can be set.
 * @param fn the function used to test the identity for each possible variable
 * assignments.
 * @param counter_example a counter example for why the identity does not hold.
 * If the identity holds for all tests, then counter_example is left unchanged.
 * @return whether the identity was verified for all the possible combinations
 * with the given elements or not.
 */
static bool
test_identity (char *               identity,
               void *               elems,
               size_t               nr_elems,
               __ap_identity_tester fn,
               __va_assignment_t ** counter_example)
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

  char *vars[nr_splits_1 + nr_splits_2];

  size_t nr_vars = get_mapped_splits (splits_1,
                                      nr_splits_1,
                                      splits_2,
                                      nr_splits_2,
                                      mapped_splits_1,
                                      mapped_splits_2,
                                      vars);


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
        if (counter_example != NULL && !oks[i] && beg + 1 == nr_vars)
        {
          *counter_example = __va_create_variable_assignment ();
          for (size_t j = 0; j < nr_vars; j++)
          {
            __va_add_variable_assignment (
              *counter_example, vars[j], tests[i][j]);
          }
          return ok;
        }
      }
      return ok;
    }
  }

  return nr_vars == 0 || test_identity (0, NULL);
}


#endif    // __ABSTRACT_POOL__
