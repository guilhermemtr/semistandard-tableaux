#ifndef __PM_TYPES__
#define __PM_TYPES__

#include <stdint.h>
#include <stdlib.h>

typedef uint64_t
                 __matroid_cell_val_t;    //!< type of the value stored in matroid cells.
typedef uint64_t __matroid_cell_tag_t;    //!< type of the tag of matroid cells.

/** Type that represents a matroid cell.
 * Type that represents a matroid cell, with the value of the cell and an
 * additional tag.
 */
typedef struct
{
  __matroid_cell_val_t val;    //!< value of the matroid cell.
  __matroid_cell_tag_t tag;    //!< tag of the matroid cell. The tag is used for
                               //!< displaying purposes.
} __matroid_cell_t;

/** Enum that represents the return values for the place function (of the
 * __pm_ordered_array_t). Enum that represents the return values for the place
 * function (of the __pm_ordered_array_t).
 */
typedef enum __pm_ordered_array_place_result {
  APPENDED, /*!< Enum value APPENDED. */
  REPLACED, /*!< Enum value REPLACED. */
} __pm_ordered_array_place_result_t;

#endif    // __PM_TYPES__
