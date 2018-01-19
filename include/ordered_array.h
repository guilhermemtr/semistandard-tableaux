#ifndef __PM_ORDERED_ARRAY__
#define __PM_ORDERED_ARRAY__

#define __PM_ORDERED_ARRAY_DEFAULT_SIZE (1 << 5)

#include <stdlib.h>

#include "types.h"

/** Structure that represents a row of a plactic matroid.
 * Structure that represents an ordered array, corresponding to a row of a
 * plactic matroid.
 */
typedef struct
{
  size_t size;    //!< true size of the ordered array.
  size_t
    counter;    //!< number of positions of the array used. invariant: counter
                //!< <= size.
  __matroid_cell_t *array;    //!< array.
} __pm_ordered_array_t;

/** Creates an ordered array to be used in plactic monoids.
 * Creates an ordered array to be used in plactic monoids.
 * @param _pmoa pointer to the structure where the array should be created.
 */
void
__pm_ordered_array_create (const __pm_ordered_array_t *_pmoa);

/** Destroys the array.
 * Destroys the array, freeing all the space allocated.
 * @param _pmoa the plactic monoid ordered array.
 */
void
__pm_ordered_array_destroy (const __pm_ordered_array_t *_pmoa);

/** Places a new element into the ordered array, possibly returning the replaced
 * element. Places a new element into the ordered array. If the new element is
 * appended to the array, APPENDED is returned; otherwise, REPLACED is returned,
 * and the value of the replaced element is written in the replaced parameter.
 * @param _pmoa the plactic monoid ordered array.
 * @param to_place the element to be placed in the array.
 * @param replaced pointer to a variable where the function can write the value
 * replaced.
 * @return APPENDED if the element was appended, or REPLACED if the element
 * replaced another previously stored element.
 */
__pm_ordered_array_place_result_t
__pm_ordered_array_place (const __pm_ordered_array_t *_pmoa,
                          const __matroid_cell_t      to_place,
                          const __matroid_cell_t *    replaced);

#endif    // __PM_ORDERED_ARRAY__
