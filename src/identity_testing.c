#include "identity_testing.h"

#ifdef __IDENTITY_TESTING__

__it_assignment_t *
__it_create_variable_assignment ()
{
  __it_assignment_t *assig = malloc (sizeof (__it_assignment_t));
  assig->size              = __IT_VARIABLE_ASSIGNMENT_DEFAULT_SIZE;
  assig->counter           = 0;
  assig->variables         = malloc (assig->size * sizeof (char *));
  assig->entries           = malloc (assig->size * sizeof (size_t));
  return assig;
}

static void
__it_resize_to (__it_assignment_t *assig, size_t sz)
{
  if (assig->counter > sz)
  {
    sz = assig->counter;
  }

  assig->size      = sz;
  assig->variables = realloc (assig->variables, assig->size * sizeof (char *));
  assig->entries   = realloc (assig->entries, assig->size * sizeof (size_t));
}

void
__it_add_variable_assignment (__it_assignment_t *_it_a, char *var, size_t idx)
{
  if (_it_a->counter == _it_a->size)
  {
    __it_resize_to (_it_a, (_it_a->size + 1) << 1);
  }

  char *str = malloc ((1 + strlen (var)) * sizeof (char));
  strcpy (str, var);

  _it_a->variables[_it_a->counter] = str;
  _it_a->entries[_it_a->counter++] = idx;
}

void
__it_destroy_variable_assignment (__it_assignment_t *_it_a)
{
  for (size_t i = 0; i < _it_a->counter; i++)
  {
    free (_it_a->variables[i]);
  }

  free (_it_a->entries);
  free (_it_a->variables);
  free (_it_a);
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

bool
__it_test_identity (char *              identity,
                    void *              elems,
                    size_t              nr_elems,
                    identity_testing    fn,
                    __it_assignment_t **counter_example)
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
          *counter_example = __it_create_variable_assignment ();
          for (size_t j = 0; j < nr_vars; j++)
          {
            __it_add_variable_assignment (
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

#endif    // __IDENTITY_TESTING__
