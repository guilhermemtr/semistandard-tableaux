#ifndef __SST_TABLEAUX_WORD__
#define __SST_TABLEAUX_WORD__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <string.h>

#include "types.h"
#include "semistandard_tableaux.h"

typedef struct __sst __sst_t;

/** Structure that represents a semistandard tableaux in the word format.
 * Structure that represents a semistandard tableaux in the word format.
 */
typedef struct __sst_word
{
  size_t size;       //!< size of the shortened tableaux.
  size_t counter;    //!< counter of the shortened tableaux. invariant: counter
                     //!< <= size.
  __tableaux_cell_t *cells;    //!< tableaux cells.
} __sst_word_t;

/** Creates a new semistandard tableaux in the word format.
 * Creates a new semistandard tableaux in the word format.
 * @return the new semistandard tableaux in the word format.
 */
__sst_word_t *
__sst_tableaux_word_create (const __sst_t *_sst);

/** Duplicates a semistandard tableaux in the word format.
 * Duplicates the given semistandard tableaux in the word format.
 * @param t the tableaux in the word format to be duplicated.
 * @return the duplicated semistandard tableaux in the word format.
 */
__sst_word_t *
__sst_tableaux_word_duplicate (const __sst_word_t *t);

/** Destroys a semistandard tableaux in the word format. Destroys a semistandard
 * tableaux in the word format, freeing all memory allocated by the tableaux.
 * @param _wsst the semistandard tableaux word structure in the word format to
 * be destroyed.
 */
void
__sst_tableaux_word_destroy (__sst_word_t *_wsst);

/** Returns the total number of cells of the shortened semistandard tableaux
 * word. Returns the total number of cells of the shortened semistandard
 * tableaux word.
 * @param _wsst the semistandard tableaux word.
 * @return the total number of cells of the shortened semistandard tableaux
 * word.
 */
size_t
__sst_tableaux_word_size (const __sst_word_t *_wsst);

/** Returns the total number of cells of the non-shortened semistandard
 * tableaux word. Returns the number of cells of the non-shortened semistandard
 * tableaux word.
 * @param _wsst the semistandard tableaux word.
 * @return the number of cells of the non-shortened semistandard tableaux word.
 */
size_t
__sst_tableaux_word_storage_size (const __sst_word_t *_wsst);

/** Verifies if two tableaux are equal. Verifies if the two given tableaux are
 * equal.
 * @param _wsst_left the first tableaux word.
 * @param _wsst_right the second tableaux word.
 * @return whether the tableaux are equal or not.
 */
bool
__sst_tableaux_word_equals (const __sst_word_t *_wsst_left,
                            const __sst_word_t *_wsst_right);

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
__sst_tableaux_word_check_identity (size_t *x,
                                    size_t  len_x,
                                    size_t *y,
                                    size_t  len_y,
                                    size_t *assigns,
                                    size_t  nr_vars,
                                    void *  elems);

/** Prints the given semistandard tableaux in the shortened word format into
 * stdout. Prints the given semistandard tableaux in the shortened word format
 * into stdout.
 * @param _wsst the word format shortened semistandard tableaux to be printed.
 */
void
__sst_tableaux_word_print (const __sst_word_t *_wsst);

/** Prints the given semistandard tableaux in the shortened word format into
 * stdout, as a table. Prints the given semistandard tableaux in the shortened
 * word format into stdout, as a table.
 * @param _wsst the word format shortened semistandard tableaux to be printed.
 */
void
__sst_tableaux_word_to_table_print (const __sst_word_t *_wsst);

/** Prints the given semistandard tableaux word in the shortened word format
 * into stdout, as a plain table. Prints the given semistandard tableaux word in
 * the shortened word format into stdout, as a plain table.
 * @param _wsst the word format shortened semistandard tableaux to be printed.
 */
void
__sst_tableaux_word_to_table_plain_print (const __sst_word_t *_wsst);

/** Prints the given semistandard tableaux in the plain word format into stdout.
 * Prints the given semistandard tableaux in the plain word format into stdout.
 * @param _sst the word format shortened semistandard tableaux to be printed.
 */
void
__sst_tableaux_word_plain_print (const __sst_word_t *_sst);

#endif    // __SST_TABLEAUX_WORD__
