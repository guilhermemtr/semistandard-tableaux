#include "tuple.h"

#ifdef __TUPLE__

__tuple_t *
__tuple_create (__tuple_entry_data *entries, size_t len)
{
  __tuple_t *t = malloc (sizeof (__tuple_t));
  t->entries   = malloc (len * sizeof (__tuple_entry_data));
  t->len       = len;
  for (size_t i = 0; i < len; i++)
  {
    t->entries[i].e       = entries[i].e;
    t->entries[i].tester  = entries[i].tester;
    t->entries[i].equals  = entries[i].equals;
    t->entries[i].destroy = entries[i].destroy;
    t->entries[i].print   = entries[i].print;
    t->entries[i].mult    = entries[i].mult;
  }
  return t;
}

void
__tuple_destroy (__tuple_t *t)
{
  for (size_t i = 0; i < t->len; i++)
  {
    (*t->entries[i].destroy) (t->entries[i].e);
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
    // check if the elements seem of the same type, by checking if the
    // multiplication algorithm is the same
    bool same_mult   = l->entries[counter].mult == r->entries[counter].mult;
    bool same_equals = l->entries[counter].equals == r->entries[counter].equals;
    if (!same_mult || !same_equals)
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
    (*t_1->entries[i].mult) (
      t_1->entries[i].e, t_2->entries[i].e, t_res->entries[i].e);
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
    if (!(*l->entries[counter].equals) (l->entries[counter].e,
                                        r->entries[counter].e))
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
  return false;
}

void
__tuple_print (__tuple_t *_tuple)
{
  printf ("Tuple: {\n");
  for (size_t counter = 0; counter < _tuple->len; counter++)
  {
    printf ("[%lu]:\n", counter);
    (*_tuple->entries[counter].print) (_tuple->entries[counter].e);
  }
  printf ("}\n");
}

#endif    // __TUPLE__
