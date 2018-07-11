#ifndef __TUPLE__
#define __TUPLE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <assert.h>

#include "types.h"

typedef struct
{
  void *                e;
  __ap_identity_tester *tester;
  __ap_equals *         equals;
  __ap_op *             destroy;
  __ap_op *             print;
  __ap_mult *           mult;
} __tuple_entry_data;

/**
 * Represents a tuple.
 */
typedef struct
{
  __tuple_entry_data *entries;
  size_t              len;
} __tuple_t;

/** Creates a new tuple.
 * Creates a new tuple, initializing all the entries.
 * @param entries an array with the entries of the tuple.
 * @param len the number of entries of the tuple.
 * @return a new tuple with the given entries.
 */
__tuple_t *
__tuple_create (__tuple_entry_data *entries, size_t len);

/** Destroys the given tuple.
 * Destroys the given tuple.
 * @param _t the tuple to be destroyed.
 */
void
__tuple_destroy (__tuple_t *_t);

/** Multiplies two tuples using the direct product, and storing the result into
 * the third argument. Multiplies two tuples using the direct product, and
 * storing the result into the third argument. The tuples must have exactly the
 * same length (i.e. the same number of entries), and the entries must be of the
 * same type.
 * @param t_1 the first tuple.
 * @param t_2 the second tuple.
 * @param t_res the resulting tuple.
 */
void
__tuple_mult (__tuple_t *t_1, __tuple_t *t_2, __tuple_t *t_res);

/** Verifies if two tuples are equal.
 * Verifies if two tuples are equal.
 * @param l the first tuple.
 * @param r the second tuple.
 * @return whether the tuples are equal or not.
 */
bool
__tuple_equals (__tuple_t *l, __tuple_t *r);

/** Verifies the validity of an identity, given a variable assignment.
 * Verifies the validity of an identity, given a variable assignment and the
 * identity.
 * @param x the left side of the identity.
 * @param len_x the length of the left side of the identity.
 * @param y the right side of the identity.
 * @param len_y the length of the right side of the identity.
 * @param assigns the assignments to the variables.
 * @param nr_vars the number of variables.
 * @param elems the elements to which the variables can be set.
 * @return whether the identity was verified for the given assignment or not.
 */
bool
__tuple_check_identity (size_t *x,
                        size_t  len_x,
                        size_t *y,
                        size_t  len_y,
                        size_t *assigns,
                        size_t  nr_vars,
                        void *  elems);

/** Prints the given tuple.
 * Prints the given tuple.
 * @param _tuple the tuple to be printed.
 */
void
__tuple_print (__tuple_t *_tuple);

#endif    // __TUPLE__
