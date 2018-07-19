#include "tuple.h"

#ifdef __TUPLE__

static const char *dir_suffix = ".entries";

__tuple_t *
__tuple_create (__tuple_entry_data_t **entries, size_t len)
{
  __tuple_t *t = malloc (sizeof (__tuple_t));
  t->entries   = malloc (len * sizeof (__tuple_entry_data_t *));
  t->len       = len;
  for (size_t i = 0; i < len; i++)
  {
    t->entries[i]                  = malloc (sizeof (__tuple_entry_data_t));
    t->entries[i]->e               = (*entries[i]->clone) (entries[i]->e);
    t->entries[i]->type            = entries[i]->type;
    t->entries[i]->tester          = entries[i]->tester;
    t->entries[i]->equals          = entries[i]->equals;
    t->entries[i]->destroy         = entries[i]->destroy;
    t->entries[i]->print           = entries[i]->print;
    t->entries[i]->mult            = entries[i]->mult;
    t->entries[i]->clone           = entries[i]->clone;
    t->entries[i]->read            = entries[i]->read;
    t->entries[i]->write           = entries[i]->write;
    t->entries[i]->entry_generator = entries[i]->entry_generator;
  }
  return t;
}

__tuple_t *
__tuple_duplicate (__tuple_t *t)
{
  return __tuple_create (t->entries, t->len);
}

void
__tuple_destroy (__tuple_t *t)
{
  for (size_t i = 0; i < t->len; i++)
  {
    (*t->entries[i]->destroy) (t->entries[i]->e);
  }
  free (t->entries);
  free (t);
}

/** Checks if two tuples seem to be of the same type.
 * Checks if two tuples seem to be of the same type.
 * @param l the first tuple.
 * @param r the second tuple.
 * @return whether the two tuples seem of the same type or not.
 */
static bool
__tuple_same_type (__tuple_t *l, __tuple_t *r)
{
  if (l->len != r->len)
  {
    return false;
  }

  for (size_t counter = 0; counter < l->len; counter++)
  {
    if (!(l->entries[counter]->type == r->entries[counter]->type))
    {
      return false;
    }
  }
  return true;
}

void
__tuple_mult (__tuple_t *t_1, __tuple_t *t_2, __tuple_t *t_res)
{
  if (!(__tuple_same_type (t_1, t_2) && __tuple_same_type (t_2, t_res)))
  {
    return;    // should actually exit, because the multiplication is not well
               // defined if the tuples are of different length.
  }
  for (size_t i = 0; i < t_1->len; i++)
  {
    (*t_1->entries[i]->mult) (
      t_1->entries[i]->e, t_2->entries[i]->e, t_res->entries[i]->e);
  }
}

bool
__tuple_equals (__tuple_t *l, __tuple_t *r)
{
  if (!__tuple_same_type (l, r))
  {
    return false;
  }
  for (size_t counter = 0; counter < l->len; counter++)
  {
    if (!(*l->entries[counter]->equals) (l->entries[counter]->e,
                                         r->entries[counter]->e))
    {
      return false;
    }
  }
  return true;
}

bool
__tuple_check_identity (size_t *x,
                        size_t  len_x,
                        size_t *y,
                        size_t  len_y,
                        size_t *assigns,
                        size_t  nr_vars,
                        void *  elems)
{
  __tuple_t **tuples = (__tuple_t **) elems;

  __tuple_t *left_curr = __tuple_duplicate (tuples[assigns[x[0]]]);
  __tuple_t *left_res  = __tuple_duplicate (tuples[assigns[x[0]]]);

  __tuple_t *right_curr = __tuple_duplicate (tuples[assigns[y[0]]]);
  __tuple_t *right_res  = __tuple_duplicate (tuples[assigns[y[0]]]);


  for (size_t i = 1; i < len_x; i++)
  {
    assert (__tuple_same_type (left_curr, tuples[assigns[x[i]]]));
    __tuple_mult (left_curr, tuples[assigns[x[i]]], left_res);
    __tuple_t *tmp = left_res;
    left_res       = left_curr;
    left_curr      = tmp;
  }

  for (size_t i = 1; i < len_y; i++)
  {
    assert (__tuple_same_type (right_curr, tuples[assigns[y[i]]]));
    __tuple_mult (right_curr, tuples[assigns[y[i]]], right_res);
    __tuple_t *tmp = right_res;
    right_res      = right_curr;
    right_curr     = tmp;
  }

  bool identity_checks = __tuple_equals (left_res, right_res);

  __tuple_destroy (left_curr);
  __tuple_destroy (left_res);
  __tuple_destroy (right_curr);
  __tuple_destroy (right_res);

  return identity_checks;
}

void
__tuple_print (__tuple_t *_tuple)
{
  printf ("Tuple: {\n");
  for (size_t counter = 0; counter < _tuple->len; counter++)
  {
    printf ("[%lu]:\n", counter);
    (*_tuple->entries[counter]->print) (_tuple->entries[counter]->e);
  }
  printf ("}\n");
}

static __tuple_entry_data_t **
__tuple_read_entries (char *filenames[], size_t count)
{
  // Open each of the tuples
  // Check what type of tuple it is.
  //
  __tuple_entry_data_t **entries =
    malloc (count * sizeof (__tuple_entry_data_t *));

  size_t num_types = 4;
  char * suffixes[num_types];
  for (size_t i = 0; i < num_types; i++)
  {
    suffixes[i] =
      __utils_concat_strings (2, get_structure_type_string (i), ".");
  }

  for (size_t i = 0; i < count; i++)
  {
    // check for each element of the enum, if the filename ends that way.
    //   for each type, pre-pend a . to the suffix
    //   check if the suffix match
    //   if no suffix matches, free everything and just return NULL
    if (__utils_str_suffix_match (filenames[i], suffixes[0]))
    {    // sst
      __sst_t *t = __sst_tableaux_read (filenames[i]);
      entries[i] = __sst_tableaux_entry_data_create (t);
      __sst_tableaux_destroy (t);
    } else if (__utils_str_suffix_match (filenames[i], suffixes[1]))
    {    // sstt
      __sst_word_t *w = __sst_tableaux_word_read (filenames[i]);
      entries[i]      = __sst_tableaux_word_tuple_entry_data_create (w);
      __sst_tableaux_word_destroy (w);
    } else if (__utils_str_suffix_match (filenames[i], suffixes[2]))
    {    // trmt
      __tm_t *tm = __tm_read (filenames[i]);
      entries[i] = __tm_tuple_entry_data_create (tm);
      __tm_destroy (tm);
    } else if (__utils_str_suffix_match (filenames[i], suffixes[3]))
    {
      __tuple_t *t = __tuple_read_plain (filenames[i]);
      entries[i]   = __tuple_tuple_entry_data_create (t);
      __tuple_destroy (t);
    } else
    {
      // There are more things that should be freed, but since this should never
      // happen, we do not deal with that.
      // In particular, everything with index < i should be freed.
      return NULL;
    }
  }

  // Should never happen
  for (size_t i = 0; i < num_types; i++)
  {
    free (suffixes[i]);
  }

  return entries;
}

__tuple_t *
__tuple_read_plain (char *fn)
{
  size_t sz        = (1 << 5);
  size_t count     = 0;
  char **filenames = calloc (sz, sizeof (char *));

  FILE *f = fopen (fn, "r");
  if (f == NULL)
  {
    return NULL;
  }

  int    read;
  size_t len = 0;

  while ((read = getline (&(filenames[count++]), &len, f)) != -1)
  {
    if (count == sz)
    {
      sz        = sz << 1;
      filenames = realloc (filenames, sz * sizeof (char *));
      for (size_t i = count; i < sz; i++)
      {
        filenames[i] = NULL;
      }
    }
  }

  fclose (f);

  __tuple_entry_data_t **entries = __tuple_read_entries (filenames, count);

  for (size_t i = 0; i < count; i++)
  {
    free (filenames[i]);
  }
  free (filenames);


  __tuple_t *t = malloc (sizeof (__tuple_t));
  t->len       = count;
  t->entries   = entries;
  return t;
}

void
__tuple_write_plain (__tuple_t *t, char *fn)
{
  char *dir_path = __utils_concat_strings (2, fn, dir_suffix);
  if (mkdir (dir_path, 0644) != 0)
  {
    // Failed to create the directory.
    return;
  }

  char *base_path = __utils_concat_strings (2, dir_path, "/");
  free (dir_path);

  char *filenames[t->len];
  for (size_t i = 0; i < t->len; i++)
  {
    char id[t->len];    // log of t->len would be enough, but I'm too lazy and
                        // it should work anyway :)
    sprintf (id, "%lu", i);
    char *fn_ext = id;    //__utils_get_filename (id, t->entries[i]->type); //
                          //The custom write function should already
                          //automatically append the file type suffix.
    char *full_fn = __utils_concat_strings (2, base_path, fn_ext);
    free (fn_ext);
    filenames[i] = full_fn;
  }

  free (base_path);

  FILE *f = fopen (fn, "w");
  if (f == NULL)
  {
    return;
  }

  for (size_t i = 0; i < t->len; i++)
  {
    (t->entries[i]->write) (t->entries[i]->e, filenames[i]);
    fprintf (f, "%s\n", filenames[i]);
    free (filenames[i]);
  }

  fclose (f);
}

__tuple_t *
__tuple_read (char *filename)
{
  char *     fn  = __utils_get_filename (filename, tup);
  __tuple_t *res = __tuple_read_plain (fn);
  free (fn);
  return res;
}

void
__tuple_write (__tuple_t *t, char *filename)
{
  char *fn = __utils_get_filename (filename, tup);
  __tuple_write_plain (t, fn);
  free (fn);
}

__tuple_entry_data_t *
__tuple_tuple_entry_data_create (__tuple_t *t)
{
  __tuple_entry_data_t *entry = malloc (sizeof (__tuple_entry_data_t));
  entry->e                    = __tuple_duplicate (t);
  entry->type                 = tup;
  entry->tester               = (__ap_identity_tester *) __tuple_check_identity;
  entry->equals               = (__ap_equals *) __tuple_equals;
  entry->destroy              = (__ap_op *) __tuple_destroy;
  entry->print                = (__ap_op *) __tuple_print;
  entry->mult                 = (__ap_mult *) __tuple_mult;
  entry->clone                = (__ap_clone *) __tuple_duplicate;
  entry->read                 = (__ap_read *) __tuple_read;
  entry->write                = (__ap_write *) __tuple_write;
  entry->entry_generator =
    (__ap_tuple_entry_data_create *) __tuple_tuple_entry_data_create;
  return entry;
}

#endif    // __TUPLE__