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
  __sst_ordered_array_t *columns;    //!< tableaux columns.
} __sst_tableaux_t;

/** Type of function that is called during iterations of tableauxs.
 * Type of function that is called during iterations of tableauxs.
 * @param cell the value of the cell currently being iterated.
 * @param index the index of the cell.
 * @param data pointer to additional data.
 * @return the offset that the iterator should go to (-1 being to go to the
 * previous position, 0 to stay still and 1 to move to the next cell of the
 * tableaux).
 */
typedef ptrdiff_t (iteration_function) (__tableaux_cell_t cell,
                                        size_t           sz,
                                        void *           data);

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
__sst_tableaux_init (__sst_tableaux_t *        _sst,
                   const __tableaux_cell_t *_sst_values,
                   const size_t            sz);

/** Destroys a semistandard tableaux, freeing all memory allocated by the tableaux.
 * Destroys a semistandard tableaux, freeing all memory allocated by the tableaux.
 * @param _sst the semistandard tableaux structure to be destroyed.
 */
void
__sst_tableaux_destroy (__sst_tableaux_t *_sst);

/** Iterates a semistandard tableaux using the column technique.
 * Iterates a semistandard tableaux using the column technique, invoking the function
 * passed as parameter for each value iterated.
 * @param _sst the semistandard tableaux.
 * @param fn the function to be called.
 * @param data additional data to be passed to the iteration function.
 */
void
__sst_tableaux_iterate_tableaux (const __sst_tableaux_t *_sst,
                              iteration_function    fn,
                              void *                data);

/** Returns the total number of cells of the semistandard tableaux.
 * Returns the total number of cells of the semistandard tableaux.
 * @param _sst the semistandard tableaux.
 * @return the total number of cells of the semistandard tableaux.
 */
size_t
__sst_tableaux_size (const __sst_tableaux_t *_sst);


/** Reads a semistandard tableaux into a vector of numbers.
 * Reads a semistandard tableaux into a vector of numbers (or, in other words, returns
 * a semistandard tableaux's word).
 * @param _sst the semistandard tableaux.
 * @param the vector of numbers corresponding to the semistandard tableaux.
 * @return the size of the tableaux cells vector.
 */
size_t
__sst_tableaux_read_tableaux (const __sst_tableaux_t *       _sst,
                           const __tableaux_cell_val_t **_sst_tableaux_cells);

/** Sets the tag of each semistandard tableaux cell.
 * Sets the tag of each semistandard tableaux cell to the given value.
 * @param _sst the semistandard tableaux.
 * @param tag the value of the tag.
 */
void
__sst_tableaux_apply_tag (__sst_tableaux_t *_sst, const __tableaux_cell_tag_t tag);

/** Multiplies two semistandard tableauxs given as input into a semistandard tableaux also
 * given as input. Multiplies the two semistandard tableauxs given as input, writing
 * the new semistandard tableaux in the third input parameter.
 * @param _sst_left the first semistandard tableaux.
 * @param _sst_right the second semistandard tableaux.
 * @param _sst_result the resulting semistandard tableaux.
 */
void
__sst_tableaux_multiply (const __sst_tableaux_t *_sst_left,
                       const __sst_tableaux_t *_sst_right,
                       __sst_tableaux_t *      _sst_result);

/** Verifies if the semistandard tableaux given as input is ok.
 * Verifies if the semistandard tableaux given as input is ok.
 * @param _sst the semistandard tableaux.
 */
bool
__sst_tableaux_check (const __sst_tableaux_t *_sst);

/** Reads a semistandard tableaux from a file.
 * Reads a semistandard tableaux from the file with the given filename.
 * @param filename the name of the file from which the semistandard tableaux is to be
 * read.
 * @return _sst the semistandard tableaux read.
 */
__sst_tableaux_t *
__sst_tableaux_read_file (const char *filename);

/** Writes the given semistandard tableaux into a file.
 * Writes the given semistandard tableaux into a file.
 * @param _sst the semistandard tableaux to be written to a file.
 * @param filename the filename of the file where the semistandard tableaux will be
 * stored.
 */
void
__sst_tableaux_write_file (const __sst_tableaux_t *_sst, const char *filename);

#endif    // __SST_TABLEAUX__
