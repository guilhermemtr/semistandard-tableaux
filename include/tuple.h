#ifndef __TUPLE__
#define __TUPLE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#include <assert.h>

#include "types.h"
#include "utils.h"

/**
 * Represents a tuple.
 */
typedef struct
{
  __tuple_entry_data_t *entries;
  size_t                len;
} __tuple_t;

/** Creates a new tuple.
 * Creates a new tuple, initializing all the entries.
 * @param entries an array with the entries of the tuple.
 * @param len the number of entries of the tuple.
 * @return a new tuple with the given entries.
 */
__tuple_t *
__tuple_create (__tuple_entry_data_t *entries, size_t len);

/** Duplicates a tuple.
 * Duplicates a tuple.
 * @param t the tuple to be duplicated.
 * @return the clone of the tuple.
 */
__tuple_t *
__tuple_duplicate (__tuple_t *t);

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

/** Reads a tuple from a file.
 * Reads a tuple from a file.
 * @param fn the filename.
 * @return the tuple read.
 */
__tuple_t *
__tuple_read_plain (char *fn);

/** Writes the tuple into a file.
 * Writes the tuple into a file.
 * @param t the tuple to be written.
 * @param fn the filename.
 */
void
__tuple_write_plain (__tuple_t *t, char *fn);

/** Reads a tuple from a file, given the filename without the suffix (which is
 * assumed to be .tup). Reads a tuple from a file, given the filename without
 * the suffix (which is assumed to be .tup).
 * @param fn the filename without the suffix.
 * @return the tuple read.
 */
__tuple_t *
__tuple_read (char *fn);

/** Writes the tuple into a file, given the filename without the suffix (which
 * is assumed to be .tup). Writes the tuple into a file, given the filename
 * without the suffix (which is assumed to be .tup).
 * @param t the tuple to be written.
 * @param fn the filename without the suffix.
 */
void
__tuple_write (__tuple_t *t, char *fn);

/** Creates a tuple entry given a tuple.
 * Creates a tuple entry given a tuple.
 * @param t the tuple.
 * @return the tuple entry data.
 */
__tuple_entry_data_t *
__tuple_tuple_entry_data_create (const __tuple_t *t);

#endif    // __TUPLE__
