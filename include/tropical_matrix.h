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

#endif    // __TROPICAL_MATRICES__
