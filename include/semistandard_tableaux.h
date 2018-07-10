#ifndef __SST_TABLEAUX__
#define __SST_TABLEAUX__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ordered_array.h"
#include "types.h"
#include "semistandard_tableaux_word.h"

/** Structure that represents a semistandard tableaux.
 * Structure that represents a semistandard tableaux, in the two dimensional
 * form.
 */
typedef struct __sst
{
  size_t size;       //!< number of rows.
  size_t counter;    //!< number of rows used. invariant: counter <= size.
  __sst_ordered_array_t *rows;    //!< tableaux rows.
} __sst_t;

typedef struct __sst_word __sst_word_t;

/** Type of function that is called during iterations of tableaux.
 * Type of function that is called during iterations of tableaux.
 * @param cell the value of the cell currently being iterated.
 * @param index the index of the cell.
 * @param real_index the true index of the cell (i.e. its non shortened
 * position).
 * @param data pointer to additional data passed as parameter.
 * @return the offset that the iterator should go to (-1 being to go to the
 * previous position, 0 to stay still and 1 to move to the next cell of the
 * tableaux).
 */
typedef ptrdiff_t (iteration_function) (__tableaux_cell_t cell,
                                        size_t            index,
                                        size_t            real_index,
                                        void *            data);

/** Creates a new semistandard tableaux.
 * Creates a new semistandard tableaux with the default size.
 * @return the new semistandard tableaux.
 */
__sst_t *
__sst_tableaux_create (void);

/** Creates a new semistandard tableaux in the word format, given one in the
 * table format. Creates a new semistandard tableaux in the word format, given
 * one in the table format.
 * @param the semistandard tableaux in the table format.
 * @return the new semistandard tableaux in the word format.
 */
__sst_t *
__sst_tableaux_table_create (const __sst_word_t *_wsst);

/** Duplicates a semistandard tableaux.
 * Duplicates the given semistandard tableaux.
 * @param t the tableaux to be duplicated.
 * @return the duplicated semistandard tableaux.
 */
__sst_t *
__sst_tableaux_duplicate (const __sst_t *t);

/** Initializes the semistandard tableaux.
 * Initializes the semistandard tableaux with the values passed as parameter.
 * @param _sst the semistandard tableaux.
 * @param _sst_values the values to initialize the semistandard tableaux with.
 * @param the length of the word (from which the tableaux is being built).
 */
void
__sst_tableaux_init (__sst_t *          _sst,
                     __tableaux_cell_t *_sst_values,
                     const size_t       sz);

/** Destroys a semistandard tableaux. Destroys a semistandard tableaux, freeing
 * all memory allocated by the tableaux.
 * @param _sst the semistandard tableaux structure to be destroyed.
 */
void
__sst_tableaux_destroy (__sst_t *_sst);

/** Iterates a semistandard tableaux using the column technique.
 * Iterates a semistandard tableaux using the column technique, invoking the
 * function passed as parameter for each cell iterated.
 * @param _sst the semistandard tableaux.
 * @param fn the function to be called.
 * @param data additional data to be passed to the iteration function.
 * @return the real size of the tableaux.
 */
size_t
__sst_tableaux_iterate_tableaux (const __sst_t *    _sst,
                                 iteration_function fn,
                                 void *             data);

/** Returns the total number of cells of the shortened semistandard tableaux.
 * Returns the total number of cells of the shortened semistandard tableaux.
 * @param _sst the semistandard tableaux.
 * @return the total number of cells of the shortened semistandard tableaux.
 */
size_t
__sst_tableaux_size (const __sst_t *_sst);

/** Returns the total number of cells of the non-shortened semistandard
 * tableaux. Returns the number of cells of the non-shortened semistandard
 * tableaux.
 * @param _sst the semistandard tableaux.
 * @return the number of cells of the non-shortened semistandard tableaux.
 */
size_t
__sst_tableaux_storage_size (const __sst_t *_sst);

/** Verifies if two tableaux are equal. Verifies if the two given tableaux are
 * equal.
 * @param _sst_left the first tableaux.
 * @param _sst_right the second tableaux.
 * @return whether the tableaux are equal or not.
 */
bool
__sst_tableaux_equals (const __sst_t *_sst_left, const __sst_t *_sst_right);

/** Reads a semistandard tableaux into a vector of numbers.
 * Reads a semistandard tableaux into a vector of numbers (or, in other words,
 * returns a semistandard tableaux's non-shortened word).
 * @param _sst the semistandard tableaux.
 * @param the vector of numbers corresponding to the semistandard tableaux.
 */
void
__sst_tableaux_read_to_plain_tableaux (
  const __sst_t *_sst, __tableaux_cell_val_t *_sst_tableaux_cells);

/** Reads a shortened semistandard tableaux from a non-shortened vector of
 * numbers. Reads a shortened semistandard tableaux from a non-shortened vector
 * of numbers (or, in other words, returns a semistandard tableaux from the
 * given word).
 * @param _sst the semistandard tableaux.
 * @param the vector of numbers corresponding to the semistandard tableaux.
 */
void
__sst_tableaux_read_from_plain_tableaux (
  __sst_t *                    _sst,
  const __tableaux_cell_val_t *_sst_tableaux_cells,
  const size_t                 len);

/** Reads a shortened semistandard tableaux into a shortened vector of cells.
 * Reads a shortened semistandard tableaux into a shortened vector of cells
 * (or, in other words, returns a word corresponding to a compressed
 * semistandard tableaux).
 * @param _sst the semistandard tableaux.
 * @param the vector of cells corresponding to the semistandard tableaux.
 * @return the size of the compressed tableaux cells vector.
 */
size_t
__sst_tableaux_read_to_compressed_tableaux (
  const __sst_t *_sst, __tableaux_cell_t *_sst_tableaux_cells);

/** Reads a shortened semistandard tableaux from a shortened vector of cells.
 * Reads a shortened semistandard tableaux from a shortened vector of cells
 * (or, in other words, returns a shortened semistandard tableaux given its
 * shortened word).
 * @param _sst the shortened semistandard tableaux.
 * @param the shortened vector of cells corresponding to the semistandard
 * tableaux.
 */
void
__sst_tableaux_read_from_compressed_tableaux (
  __sst_t *                _sst,
  const __tableaux_cell_t *_sst_tableaux_cells,
  const size_t             len);

/** Reads a shortened semistandard tableaux from a plain file.
 * Reads a shortened semistandard tableaux from the plain file with the given
 * filename.
 * @param filename the name of the file from which the semistandard tableaux is
 * to be read.
 * @return _sst the shortened semistandard tableaux read.
 */
__sst_t *
__sst_tableaux_read_plain_file (const char *filename);

/** Writes the given shortened semistandard tableaux into a plain file.
 * Writes the given shortened semistandard tableaux into a plain file.
 * @param _sst the shortened semistandard tableaux to be written to the file.
 * @param filename the filename of the file where the shortened semistandard
 * tableaux will be stored.
 */
void
__sst_tableaux_write_plain_file (const __sst_t *_sst, const char *filename);

/** Reads a shortened semistandard tableaux from a file.
 * Reads a shortened semistandard tableaux from the file with the given
 * filename.
 * @param filename the name of the file from which the shortened semistandard
 * tableaux is to be read.
 * @return _sst the shortened semistandard tableaux read.
 */
__sst_t *
__sst_tableaux_read_compressed_file (const char *filename);

/** Writes the given shortened semistandard tableaux into a shortened file.
 * Writes the given shortened semistandard tableaux into a shortened file.
 * @param _sst the shortened semistandard tableaux to be written to a file.
 * @param filename the filename of the file where the shortened semistandard
 * tableaux will be stored.
 */
void
__sst_tableaux_write_compressed_file (const __sst_t *_sst,
                                      const char *   filename);

/** Reads a shortened semistandard tableaux from a file.
 * Reads a shortened semistandard tableaux from the file with the given
 * filename.
 * @param filename the name of the file from which the shortened semistandard
 * tableaux is to be read.
 * @return _sst the shortened semistandard tableaux read.
 */
__sst_t *
__sst_tableaux_read_table_file (const char *filename);

/** Reads a shortened semistandard tableaux from a file.
 * Reads a shortened semistandard tableaux from the file with the given
 * filename.
 * @param filename the name of the file from which the shortened semistandard
 * tableaux is to be read.
 * @return _sst the shortened semistandard tableaux read.
 */
void
__sst_tableaux_write_table_file (const __sst_t *_sst, const char *filename);

/** Prints the given shortened semistandard tableaux into stdout.
 * Prints the given shortened semistandard tableaux into stdout.
 * @param _sst the shortened semistandard tableaux to be printed.
 */
void
__sst_tableaux_print (const __sst_t *_sst);

/** Prints the given semistandard tableaux in plain format to stdout.
 * Prints the given semistandard tableaux in plain format to stdout.
 * @param _sst the shortened semistandard tableaux to be printed.
 */
void
__sst_tableaux_plain_print (const __sst_t *_sst);

/** Verifies if the shortened semistandard tableaux given as input is in proper
 * form. Verifies if the shortened semistandard tableaux given as input is in
 * proper form.
 * @param _sst the shortened semistandard tableaux.
 */
bool
__sst_tableaux_check (const __sst_t *_sst);

/** Multiplies two semistandard tableauxs given as input, and with the given
 * size into a semistandard tableaux also given as input. Multiplies the two
 * semistandard tableauxs given as input, and with the given size, writing the
 * new semistandard tableaux in the third input parameter.
 * @param _sst_left the first semistandard tableaux.
 * @param _sst_right the second semistandard tableaux.
 * @param sz_right the size of the second shortened semistandard tableaux.
 * @param _sst_result the resulting semistandard tableaux.
 * @return the size of the shortened resulting tableaux
 */
size_t
__sst_tableaux_fast_multiply (const __sst_t *_sst_left,
                              const __sst_t *_sst_right,
                              const size_t   sz_right,
                              __sst_t *      _sst_result);

/** Multiplies two semistandard tableauxs given as input into a semistandard
 * tableaux also given as input. Multiplies the two semistandard tableauxs given
 * as input, writing the new semistandard tableaux in the third input parameter.
 * @param _sst_left the first semistandard tableaux.
 * @param _sst_right the second semistandard tableaux.
 * @param _sst_result the resulting semistandard tableaux.
 */
void
__sst_tableaux_multiply (const __sst_t *_sst_left,
                         const __sst_t *_sst_right,
                         __sst_t *      _sst_result);

#endif    // __SST_TABLEAUX__
