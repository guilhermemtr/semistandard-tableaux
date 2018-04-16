#ifndef __SST_TYPES__
#define __SST_TYPES__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint64_t
  __tableaux_cell_val_t;    //!< type of the value stored in tableaux cells.
typedef uint64_t
  __tableaux_cell_len_t;    //!< type of the length of tableaux cells.

/** Type that represents a sequence of tableaux cells with the same value.
 * Type that represents a sequence of tableaux cells, with the same value, of a
 * certain length.
 */
typedef struct
{
  __tableaux_cell_val_t val;    //!< value of the tableaux cell.
  __tableaux_cell_len_t len;    //!< tableaux cell's sequence length.
} __tableaux_cell_t;

#endif    // __SST_TYPES__
