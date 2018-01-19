#ifndef __PM_MATROID__
#define __PM_MATROID__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ordered_array.h"
#include "types.h"

/** Structure that represents a plactic matroid.
 * Structure that represents a plactic matroid.
 */
typedef struct
{
  size_t size;    //!< true size of the ordered array.
  size_t
    counter;    //!< number of positions of the array used. invariant: counter
                //!< <= size.
  __pm_ordered_array_t *columns;    //!< matroid columns.
} __pm_matroid_t;

/** Type of function that is called during iterations of matroids.
 * Type of function that is called during iterations of matroids.
 * @param cell the value of the cell currently being iterated.
 * @param index the index of the cell.
 * @param data pointer to additional data.
 * @return the offset that the iterator should go to (-1 being to go to the
 * previous position, 0 to stay still and 1 to move to the next cell of the
 * matroid).
 */
typedef ptrdiff_t (iteration_function) (__matroid_cell_t cell,
                                        size_t           sz,
                                        void *           data);

/** Creates a new plactic matroid.
 * Creates a new plactic matroid with the default size.
 * @return the new plactic matroid.
 */
__pm_matroid_t *
__pm_matroid_create (void);

/** Initializes the plactic matroid .
 * Initializes the plactic matroid with the values passed as parameter.
 * @param _pm the plactic matroid.
 * @param _pm_values the values to initialize the plactic matroid with
 * @param the size of the word (from which the matroid is being built).
 */
void
__pm_matroid_init (__pm_matroid_t *        _pm,
                   const __matroid_cell_t *_pm_values,
                   const size_t            sz);

/** Destroys a plactic matroid, freeing all memory allocated by the matroid.
 * Destroys a plactic matroid, freeing all memory allocated by the matroid.
 * @param _pm the plactic matroid structure to be destroyed.
 */
void
__pm_matroid_destroy (__pm_matroid_t *_pm);

/** Iterates a plactic matroid using the column technique.
 * Iterates a plactic matroid using the column technique, invoking the function
 * passed as parameter for each value iterated.
 * @param _pm the plactic matroid.
 * @param fn the function to be called.
 * @param data additional data to be passed to the iteration function.
 */
void
__pm_matroid_iterate_matroid (const __pm_matroid_t *_pm,
                              iteration_function    fn,
                              void *                data);

/** Returns the total number of cells of the plactic matroid.
 * Returns the total number of cells of the plactic matroid.
 * @param _pm the plactic matroid.
 * @return the total number of cells of the plactic matroid.
 */
size_t
__pm_matroid_size (const __pm_matroid_t *_pm);


/** Reads a plactic matroid into a vector of numbers.
 * Reads a plactic matroid into a vector of numbers (or, in other words, returns
 * a plactic matroid's word).
 * @param _pm the plactic matroid.
 * @param the vector of numbers corresponding to the plactic matroid.
 * @return the size of the matroid cells vector.
 */
size_t
__pm_matroid_read_matroid (const __pm_matroid_t *       _pm,
                           const __matroid_cell_val_t **_pm_matroid_cells);

/** Sets the tag of each plactic matroid cell.
 * Sets the tag of each plactic matroid cell to the given value.
 * @param _pm the plactic matroid.
 * @param tag the value of the tag.
 */
void
__pm_matroid_apply_tag (__pm_matroid_t *_pm, const __matroid_cell_tag_t tag);

/** Multiplies two plactic matroids given as input into a plactic matroid also
 * given as input. Multiplies the two plactic matroids given as input, writing
 * the new plactic matroid in the third input parameter.
 * @param _pm_left the first plactic matroid.
 * @param _pm_right the second plactic matroid.
 * @param _pm_result the resulting plactic matroid.
 */
void
__pm_matroid_multiply (const __pm_matroid_t *_pm_left,
                       const __pm_matroid_t *_pm_right,
                       __pm_matroid_t *      _pm_result);

/** Verifies if the plactic matroid given as input is ok.
 * Verifies if the plactic matroid given as input is ok.
 * @param _pm the plactic matroid.
 */
bool
__pm_matroid_check (const __pm_matroid_t *_pm);

/** Reads a plactic matroid from a file.
 * Reads a plactic matroid from the file with the given filename.
 * @param filename the name of the file from which the plactic matroid is to be
 * read.
 * @return _pm the plactic matroid read.
 */
__pm_matroid_t *
__pm_matroid_read_file (const char *filename);

/** Writes the given plactic matroid into a file.
 * Writes the given plactic matroid into a file.
 * @param _pm the plactic matroid to be written to a file.
 * @param filename the filename of the file where the plactic matroid will be
 * stored.
 */
void
__pm_matroid_write_file (const __pm_matroid_t *_pm, const char *filename);

#endif    // __PM_MATROID__
