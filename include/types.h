#ifndef __SST_TYPES__
#define __SST_TYPES__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef uint64_t
  __tableaux_cell_val_t;    //!< type of the value stored in tableaux cells.

#define __TABLEAUX_CELL_VAL_FORMAT "%lu"

typedef uint64_t
  __tableaux_cell_len_t;    //!< type of the length of tableaux cells.

#define __TABLEAUX_CELL_LEN_FORMAT "%lu"

/** Type that represents a sequence of tableaux cells with the same value.
 * Type that represents a sequence of tableaux cells, with the same value, of a
 * certain length.
 */
typedef struct
{
  __tableaux_cell_val_t val;    //!< value of the tableaux cell.
  __tableaux_cell_len_t len;    //!< tableaux cell's sequence length.
} __tableaux_cell_t;


/** Type of function that corresponds to functions that verify the validity of
 * an identity, given two assignments. Type of function that corresponds to
 * functions that verify the validity of an identity, given two assignments.
 * @param x the left side of the identity.
 * @param len_x the length of the left side of the identity.
 * @param y the right side of the identity.
 * @param len_y the length of the right side of the identity.
 * @param assigns the assignments to the variables.
 * @param nr_vars the number of variables.
 * @param elems the domains of the variables.
 * @return whether the identity was verified for the given assignment or not.
 */
typedef bool(__ap_identity_tester) (size_t *x,
                                    size_t  len_x,
                                    size_t *y,
                                    size_t  len_y,
                                    size_t *assigns,
                                    size_t  nr_vars,
                                    void *  elems);

/** Type of function that corresponds to functions that verify if two elements
 * are equal. Type of function that corresponds to functions that verify if two
 * elements are equal.
 * @param e1 the first element.
 * @param e2 the second element.
 * @return whether the elements are equal or not.
 */
typedef bool(__ap_equals) (void *e1, void *e2);

/** Type of function that corresponds to functions that operate over an element.
 * Type of function that corresponds to functions that operate over an element.
 * @param e the element.
 */
typedef void(__ap_op) (void *e);

/** Type of function that corresponds to functions that perform a deep-clone of
 * an element. Type of function that corresponds to functions that perform a
 * deep-clone of an element.
 * @param e the element.
 * @return the deep clone.
 */
typedef void *(__ap_clone) (void *e);

/** Type of function that corresponds to functions that multiply two elements,
 * being that the result is stored in the third argument. Type of function that
 * corresponds to functions that multiply two elements, being that the result is
 * stored in the third argument.
 * @param e1 the first element.
 * @param e2 the second element.
 * @param res the return.
 */
typedef void(__ap_mult) (void *e1, void *e2, void *res);

/** Type of function that corresponds to functions that read an element from a
 * file. Type of function that corresponds to functions that read an element
 * from a file.
 * @param fn the filename of the file where the element is stored.
 * @return the element read.
 */
typedef void *(__ap_read) (char *fn);

/** Type of function that corresponds to functions that write an element to a
 * file. Type of function that corresponds to functions that write an element to
 * a file.
 * @param e the element.
 * @param fn the filename of the file where the element is to be stored.
 * @return the element read.
 */
typedef void(__ap_write) (void *e, char *fn);

#endif    // __SST_TYPES__
