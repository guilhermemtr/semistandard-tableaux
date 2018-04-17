#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

#ifndef __IDENTITY_TESTING__
#define __IDENTITY_TESTING__

#define __IT_DELIMITER__ "="
#define __IT_OP_SYMBOL__ "."

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
/*typedef ptrdiff_t (identity_testing) (__tableaux_cell_t cell,
                                      size_t            index,
                                      size_t            real_index,
                                      void *            data);
*/

bool
__it_test_identity (char *identity, void *elems, size_t nr_elems);


// define function for identity testing

// function that receives two

#endif    // __IDENTITY_TESTING__
