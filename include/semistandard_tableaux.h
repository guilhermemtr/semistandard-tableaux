#ifndef __SST_TABLEAUX__
#define __SST_TABLEAUX__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ordered_array.h"
#include "types.h"

/** Structure that represents a semistandard tableaux.
 * Structure that represents a semistandard tableaux.
 */
typedef struct
{
  size_t size;    //!< true size of the ordered array.
  size_t
    counter;    //!< number of positions of the array used. invariant: counter
                //!< <= size.
  __sst_ordered_array_t *rows;    //!< tableaux rows.
} __sst_tableaux_t;

/** Structure that represents a semistandard tableaux in the word format.
 * Structure that represents a semistandard tableaux in the word format.
 */
typedef struct
{
  size_t size;       //!< shortened size of the tableaux.
  size_t counter;    //!< shortened counter of the tableaux. invariant: counter
                     //!< <= size.
  __tableaux_cell_t *cells;    //!< tableaux cells.
} __sst_word_tableaux_t;

/** Type of function that is called during iterations of tableauxs.
 * Type of function that is called during iterations of tableauxs.
 * @param cell the value of the cell currently being iterated.
 * @param index the index of the cell.
 * @param real_index the true index of the cell.
 * @param data pointer to additional data.
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
__sst_tableaux_t *
__sst_tableaux_create (void);

/** Initializes the semistandard tableaux .
 * Initializes the semistandard tableaux with the values passed as parameter.
 * @param _sst the semistandard tableaux.
 * @param _sst_values the values to initialize the semistandard tableaux with
 * @param the size of the word (from which the tableaux is being built).
 */
void
__sst_tableaux_init (__sst_tableaux_t * _sst,
                     __tableaux_cell_t *_sst_values,
                     const size_t       sz);

/** Destroys a semistandard tableaux, freeing all memory allocated by the
 * tableaux. Destroys a semistandard tableaux, freeing all memory allocated by
 * the tableaux.
 * @param _sst the semistandard tableaux structure to be destroyed.
 */
void
__sst_tableaux_destroy (__sst_tableaux_t *_sst);

/** Iterates a semistandard tableaux using the column technique.
 * Iterates a semistandard tableaux using the column technique, invoking the
 * function passed as parameter for each value iterated.
 * @param _sst the semistandard tableaux.
 * @param fn the function to be called.
 * @param data additional data to be passed to the iteration function.
 * @return the real size of the tableaux.
 */
size_t
__sst_tableaux_iterate_tableaux (const __sst_tableaux_t *_sst,
                                 iteration_function      fn,
                                 void *                  data);

/** Returns the total number of cells of the semistandard tableaux.
 * Returns the total number of cells of the semistandard tableaux.
 * @param _sst the semistandard tableaux.
 * @return the total number of cells of the semistandard tableaux.
 */
size_t
__sst_tableaux_size (const __sst_tableaux_t *_sst);

/** Returns the number of cells of the representation of the semistandard
 * tableaux. Returns the number of cells of the representation of the
 * semistandard tableaux.
 * @param _sst the semistandard tableaux.
 * @return the number of cells of the representation of the semistandard
 * tableaux.
 */
size_t
__sst_tableaux_storage_size (const __sst_tableaux_t *_sst);

/** Verifies if the semistandard tableaux given as input is ok.
 * Verifies if the semistandard tableaux given as input is ok.
 * @param _sst the semistandard tableaux.
 */
bool
__sst_tableaux_check (const __sst_tableaux_t *_sst);

/** Multiplies two semistandard tableauxs given as input, and with the given
 * sizes into a semistandard tableaux also given as input. Multiplies the two
 * semistandard tableauxs given as input, and with the given sizes, writing the
 * new semistandard tableaux in the third input parameter.
 * @param _sst_left the first semistandard tableaux.
 * @param _sst_right the second semistandard tableaux.
 * @param sz_right the size of the second semistandard tableaux.
 * @param _sst_result the resulting semistandard tableaux.
 * @return the (shortened) size of the resulting tableaux
 */
size_t
__sst_tableaux_fast_multiply (const __sst_tableaux_t *_sst_left,
                              const __sst_tableaux_t *_sst_right,
                              const size_t            sz_right,
                              __sst_tableaux_t *      _sst_result);

/** Multiplies two semistandard tableauxs given as input into a semistandard
 * tableaux also given as input. Multiplies the two semistandard tableauxs given
 * as input, writing the new semistandard tableaux in the third input parameter.
 * @param _sst_left the first semistandard tableaux.
 * @param _sst_right the second semistandard tableaux.
 * @param _sst_result the resulting semistandard tableaux.
 */
void
__sst_tableaux_multiply (const __sst_tableaux_t *_sst_left,
                         const __sst_tableaux_t *_sst_right,
                         __sst_tableaux_t *      _sst_result);

/** Verifies the validity of an identity, given two assignments.
 * Verifies the validity of an identity, given two assignments and the identity.
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
__sst_tableaux_check_identity (size_t *x,
                               size_t  len_x,
                               size_t *y,
                               size_t  len_y,
                               size_t *assigns,
                               size_t  nr_vars,
                               void *  elems);

/** Reads a semistandard tableaux into a vector of numbers.
 * Reads a semistandard tableaux into a vector of numbers (or, in other words,
 * returns a semistandard tableaux's word).
 * @param _sst the semistandard tableaux.
 * @param the vector of numbers corresponding to the semistandard tableaux.
 */
void
__sst_tableaux_read_to_plain_tableaux (
  const __sst_tableaux_t *_sst, __tableaux_cell_val_t *_sst_tableaux_cells);

/** Reads a semistandard tableaux from a vector of numbers.
 * Reads a semistandard tableaux from a vector of numbers (or, in other words,
 * returns a semistandard tableaux from the given word).
 * @param _sst the semistandard tableaux.
 * @param the vector of numbers corresponding to the semistandard tableaux.
 */
void
__sst_tableaux_read_from_plain_tableaux (
  __sst_tableaux_t *           _sst,
  const __tableaux_cell_val_t *_sst_tableaux_cells,
  const size_t                 len);

/** Reads a semistandard tableaux into a compressed vector of cells.
 * Reads a semistandard tableaux into a compressed vector of cells (or, in
 * other words, returns a word corresponding to a compressed semistandard
 * tableaux).
 * @param _sst the semistandard tableaux.
 * @param the vector of cells corresponding to the semistandard tableaux.
 * @return the size of the compressed tableaux cells vector.
 */
size_t
__sst_tableaux_read_to_compressed_tableaux (
  const __sst_tableaux_t *_sst, __tableaux_cell_t *_sst_tableaux_cells);

/** Reads a semistandard tableaux from a compressed vector of cells.
 * Reads a semistandard tableaux from a compressed vector of cells (or, in
 * other words, returns a compressed semistandard tableaux given its compressed
 * word).
 * @param _sst the semistandard tableaux.
 * @param the vector of cells corresponding to the semistandard tableaux.
 */
void
__sst_tableaux_read_from_compressed_tableaux (
  __sst_tableaux_t *       _sst,
  const __tableaux_cell_t *_sst_tableaux_cells,
  const size_t             len);

/** Reads a semistandard tableaux from a plain file.
 * Reads a semistandard tableaux from the plain file with the given filename.
 * @param filename the name of the file from which the semistandard tableaux is
 * to be read.
 * @return _sst the semistandard tableaux read.
 */
__sst_tableaux_t *
__sst_tableaux_read_plain_file (const char *filename);

/** Writes the given semistandard tableaux into a plain file.
 * Writes the given semistandard tableaux into a plain file.
 * @param _sst the semistandard tableaux to be written to a plain file.
 * @param filename the filename of the file where the semistandard tableaux will
 * be stored.
 */
void
__sst_tableaux_write_plain_file (const __sst_tableaux_t *_sst,
                                 const char *            filename);

/** Reads a compressed semistandard tableaux from a file.
 * Reads a compressed semistandard tableaux from the file with the given
 * filename.
 * @param filename the name of the file from which the compressed semistandard
 * tableaux is to be read.
 * @return _sst the semistandard tableaux read.
 */
__sst_tableaux_t *
__sst_tableaux_read_compressed_file (const char *filename);

/** Writes the given semistandard tableaux into a compressed file.
 * Writes the given semistandard tableaux into a compressed file.
 * @param _sst the compressed semistandard tableaux to be written to a file.
 * @param filename the filename of the file where the compressed semistandard
 * tableaux will be stored.
 */
void
__sst_tableaux_write_compressed_file (const __sst_tableaux_t *_sst,
                                      const char *            filename);

/** Prints the given semistandard tableaux into stdout.
 * Prints the given semistandard tableaux into stdout.
 * @param _sst the compressed semistandard tableaux to be printed.
 */
void
__sst_tableaux_print (const __sst_tableaux_t *_sst);

/** Prints the given semistandard tableaux in plain format to stdout.
 * Prints the given semistandard tableaux in plain format to stdout.
 * @param _sst the compressed semistandard tableaux to be printed.
 */
void
__sst_tableaux_plain_print (const __sst_tableaux_t *_sst);


/** Prints the given semistandard tableaux in the word format into stdout.
 * Prints the given semistandard tableaux in the word format into stdout.
 * @param _sst the word format compressed semistandard tableaux to be printed.
 */
void
__sst_tableaux_word_print (const __sst_word_tableaux_t *_sst);

/** Prints the given semistandard tableaux in the plain word format into stdout.
 * Prints the given semistandard tableaux in the plain word format into stdout.
 * @param _sst the word format compressed semistandard tableaux to be printed.
 */
void
__sst_tableaux_plain_word_print (const __sst_word_tableaux_t *_sst);


#endif    // __SST_TABLEAUX__
