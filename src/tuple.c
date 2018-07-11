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
    t->entries[i].clone   = entries[i].clone;
    t->entries[i].read    = entries[i].read;
    t->entries[i].write   = entries[i].write;
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
  __tuple_t **tuples = (__tuple_t **) elems;

  __tuple_t *left_curr = __tuple_duplicate (tuples[assigns[x[0]]]);
  __tuple_t *left_res  = __tuple_duplicate (tuples[assigns[x[0]]]);

  __tuple_t *right_curr = __tuple_duplicate (tuples[assigns[y[0]]]);
  __tuple_t *right_res  = __tuple_duplicate (tuples[assigns[y[0]]]);


  for (size_t i = 1; i < len_x; i++)
  {
    __tuple_mult (left_curr, tuples[assigns[x[i]]], left_res);
    __tuple_t *tmp = left_res;
    left_res       = left_curr;
    left_curr      = tmp;
  }

  for (size_t i = 1; i < len_y; i++)
  {
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
    (*_tuple->entries[counter].print) (_tuple->entries[counter].e);
  }
  printf ("}\n");
}

__tuple_t *
__tuple_read (char *fn)
{
  // TO IMPLEMENT
  return NULL;
}

void
__tuple_write (__tuple_t *t, char *fn)
{
  // TO IMPLEMENT
}

#endif    // __TUPLE__
