#ifndef __SST_ORDERED_ARRAY__
#define __SST_ORDERED_ARRAY__

#define __SST_ORDERED_ARRAY_DEFAULT_SIZE (1 << 5)

#include <stdlib.h>
#include <string.h>

#include "types.h"

/** Structure that represents a row of a semistandard tableaux.
 * Structure that represents an ordered array, corresponding to a row of a
 * semistandard tableaux.
 */
typedef struct
{
  size_t size;    //!< true size of the ordered array.
  size_t
    counter;    //!< number of positions of the array used. invariant: counter
                //!< <= size.
  __tableaux_cell_t *array;    //!< array.
} __sst_ordered_array_t;

/** Creates an ordered array to be used in semistandard tableaux.
 * Creates an ordered array to be used in semistandard tableaux.
 * @param _sstoa pointer to the structure where the array should be created.
 */
void
__sst_ordered_array_create (__sst_ordered_array_t *_sstoa);

/** Destroys the array.
 * Destroys the array, freeing all the space allocated.
 * @param _sstoa the semistandard tableaux ordered array.
 */
void
__sst_ordered_array_destroy (__sst_ordered_array_t *_sstoa);

/** Returns the true size of the array.
 * Returns the true size of the array, taking into account the length of the
 * cells.
 * @param _sstoa the semistandard tableaux ordered array.
 * @return size the true size of the semistandard tableaux ordered array.
 */
size_t
__sst_ordered_array_real_length (__sst_ordered_array_t *_sstoa);

/** Resizes the array to be twice as long.
 * Resizes the array to be twice as long.
 * @param _sstoa the semistandard tableaux ordered array to be resized.
 */
void
__sst_ordered_array_resize (__sst_ordered_array_t *_sstoa);

/** Resizes the array to the given size.
 * Resizes the array to the given size, unless the given size is not enough to
 * store all the elements of the array. If the given size is not enough, then
 * the array is resized to _sstoa->counter.
 * @param _sstoa the semistandard tableaux ordered array to be resized.
 * @param size the new size to which the semistandard tableaux ordered array.
 */
void
__sst_ordered_array_resize_to (__sst_ordered_array_t *_sstoa, const size_t sz);

/** Copies the first array into the second.
 * Copies the first array into the second, resizing it if needed.
 * @param _sstoa_from the semistandard tableaux ordered array from which data is
 * copied.
 * @param _sstoa_to the semistandard tableaux to which the data is copied.
 */
void
__sst_ordered_array_copy (const __sst_ordered_array_t *_sstoa_from,
                          __sst_ordered_array_t *      _sstoa_to);

/** Places new elements into the ordered array, possibly returning replaced
 * elements. Places new elements into the ordered array. The returned value
 * corresponds to the number of elements that were appended to the array.
 * @param _sstoa the semistandard tableaux ordered array.
 * @param to_place the elements to be placed in the array.
 * @param nr_to_place the number of elements to be placed in the array.
 * @param replaced pointer to a variable where the function can write the values
 * replaced.
 * @return number of (compressed) elements replaced.
 */
void
__sst_ordered_array_place (__sst_ordered_array_t *_sstoa,
                           __tableaux_cell_t *    to_place,
                           size_t                 nr_to_place,
                           size_t                 real_nr_to_place,
                           __tableaux_cell_t *    replaced,
                           size_t                 nr_replaced,
                           size_t                 real_nr_replaced);

#endif    // __SST_ORDERED_ARRAY__
