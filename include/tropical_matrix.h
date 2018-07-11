#ifndef __TROPICAL_MATRICES__
#define __TROPICAL_MATRICES__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <assert.h>

#include "tropical_numbers.h"

/**
 * Represents a tropical matrix.
 */
typedef struct
{
  size_t  rows;
  size_t  columns;
  __tn_t *matrix;
} __tm_t;

/** Creates a new matrix.
 * Creates a new matrix, with all positions set to -inf.
 * @param columns the number of columns of the matrix to be created.
 * @param rows the number of rows of the matrix to be created.
 * @return the created matrix.
 */
__tm_t *
__tm_create (size_t columns, size_t rows);

/** Destroys the given matrix.
 * Destroys the given matrix.
 * @param _tm the matrix to be destroyed.
 */
void
__tm_destroy (__tm_t *_tm);

/** Sums two tropical matrices into the third tropical matrix.
 * Sums two tropical matrices into the third tropical matrix.
 * @param m1 the first tropical matrix.
 * @param m2 the second tropical matrix.
 * @param res the tropical matrix where the result will be stored.
 */
void
__tm_sum (__tm_t *m1, __tm_t *m2, __tm_t *res);

/** Multiplies two tropical matrices into the third tropical matrix.
 * Multiplies two tropical matrices into the third tropical matrix.
 * @param m1 the first tropical matrix.
 * @param m2 the second tropical matrix.
 * @param res the tropical matrix where the result will be stored.
 */
void
__tm_mult (__tm_t *m1, __tm_t *m2, __tm_t *res);

/** Verifies if two tropical matrices are equal.
 * Verifies if two tropical matrices are equal.
 * @param l the first tropical matrix.
 * @param r the second tropical matrix.
 * @return whether the tropical matrices are equal or not.
 */
bool
__tm_equals (__tm_t *l, __tm_t *r);

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
__tm_check_identity (size_t *x,
                     size_t  len_x,
                     size_t *y,
                     size_t  len_y,
                     size_t *assigns,
                     size_t  nr_vars,
                     void *  elems);

/** Reads a tropical matrix from a file with the given filename.
 * Reads a tropical matrix from a file with the given filename.
 * @param filename the filename.
 * @return the matrix read.
 */
__tm_t *
__tm_read (char *filename);

/** Writes a tropical matrix to a file with the given filename.
 * Writes a tropical matrix to a file with the given filename.
 * @param m the tropical matrix.
 * @param filename the filename.
 */
void
__tm_write (__tm_t *m, char *filename);

/** Prints the given matrix.
 * Prints the given matrix.
 * @param _tm the matrix to be printed.
 */
void
__tm_print (__tm_t *_tm);

#endif    // __TROPICAL_MATRICES__
