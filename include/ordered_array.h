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

/** Places a new element into the ordered array, possibly returning the replaced
 * element. Places a new element into the ordered array. If the new element is
 * appended to the array, APPENDED is returned; otherwise, REPLACED is returned,
 * and the value of the replaced element is written in the replaced parameter.
 * @param _sstoa the semistandard tableaux ordered array.
 * @param to_place the element to be placed in the array.
 * @param replaced pointer to a variable where the function can write the value
 * replaced.
 * @return APPENDED if the element was appended, or REPLACED if the element
 * replaced another previously stored element.
 */
__sst_ordered_array_place_result_t
__sst_ordered_array_place (__sst_ordered_array_t * _sstoa,
                          const __tableaux_cell_t to_place,
                          __tableaux_cell_t *     replaced);

/** Copies the first array into the second.
 * Copies the first array into the second, resizing it if needed.
 * @param _sstoa_from the semistandard tableaux ordered array from which data is copied.
 * @param _sstoa_to the semistandard tableaux to which the data is copied.
 */
void
__sst_ordered_array_copy (const __sst_ordered_array_t *_sstoa_from,
                         __sst_ordered_array_t *      _sstoa_to);


#endif    // __SST_ORDERED_ARRAY__
