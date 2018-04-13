#ifndef __SST_TYPES__
#define __SST_TYPES__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint64_t
  __tableaux_cell_val_t;    //!< type of the value stored in tableaux cells.
typedef uint64_t
  __tableaux_cell_tag_t;    //!< type of the tag of tableaux cells.

/** Type that represents a tableaux cell.
 * Type that represents a tableaux cell, with the value of the cell and an
 * additional tag.
 */
typedef struct
{
  __tableaux_cell_val_t val;    //!< value of the tableaux cell.
  __tableaux_cell_tag_t tag;    //!< tag of the tableaux cell. The tag is used for
                               //!< displaying purposes.
} __tableaux_cell_t;

/** Enum that represents the return values for the place function (of the
 * __sst_ordered_array_t). Enum that represents the return values for the place
 * function (of the __sst_ordered_array_t).
 */
typedef enum __sst_ordered_array_place_result {
  APPENDED, /*!< Enum value APPENDED. */
  REPLACED, /*!< Enum value REPLACED. */
} __sst_ordered_array_place_result_t;

#endif    // __SST_TYPES__
