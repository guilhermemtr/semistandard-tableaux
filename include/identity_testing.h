#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"
#include "configuration.h"

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
typedef bool(identity_testing) (size_t *x,
                                size_t  len_x,
                                size_t *y,
                                size_t  len_y,
                                size_t *assigns,
                                size_t  nr_vars);


bool
__it_test_identity (char *           identity,
                    void *           elems,
                    size_t           nr_elems,
                    identity_testing fn);


// define function for identity testing

// function that receives two

#endif    // __IDENTITY_TESTING__
