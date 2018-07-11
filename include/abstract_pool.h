#ifndef __ABSTRACT_POOL__
#define __ABSTRACT_POOL__
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <assert.h>

#include <dirent.h>
#include <sys/types.h>


#include "hashmap.h"
#include "configuration.h"
#include "variable_assignment.h"

#define __AP_DEFAULT_SIZE (1 << 5)

#define __AP_DELIMITER__ "="
#define __AP_OP_SYMBOL__ "."

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

/**Below we define a pool for abstract data structures, which are intended to
 * represent mathematical objects of some kind.
 * This pool is NOT type safe, meaning that one can add structures of multiple
 * types to the same pool. Although ideally this should not be possible, we pass
 * down to the programmer the responsibility to make sure that each pool object
 * is used only for storing a certain type of objects.
 */

/** Structure that represents a pool of some abstract structure.
 * Structure that represents a pool of some abstract structure.
 */
typedef struct
{
  size_t size;            //!< true size of the pool.
  size_t counter;         //!< size of the pool.
  void **pool_entries;    //!< entries of the pool.

  __ap_identity_tester *tester;     //!< multiplies two elements
  __ap_equals          *equals;     //!< checks if two elements are equal
  __ap_op              *destroy;    //!< destroys an element
  __ap_op              *print;      //!< prints an element
} __ap_t;

/** Creates a pool of mathematical objects.
 * Creates a pool of mathematical objects.
 * @param tester function to be used to check an equality.
 * @param equals function that checks if two elements are equal.
 * @param destroy function that destroys an element.
 * @param print function that prints an element.
 * @return the mathematical objects' pool created.
 */
__ap_t *
__ap_create_pool (__ap_identity_tester *tester,
                  __ap_equals *         equals,
                  __ap_op *             destroy,
                  __ap_op *             print);

/** Destroys a pool of mathematical objects.
 * Destroys a pool of mathematical objects.
 * @param p the mathematical objects pool to be destroyed.
 */
void
__ap_destroy_pool (__ap_t *p);

/** Function that adds an element to the pool.
 * Function that adds an element to the pool.
 * @param p the pool to which the element is to be added.
 * @param e the element to be added to the pool.
 */
void
__ap_add_element (__ap_t *p, void *e);

/** Function that tests an identity using the given pool of mathematical
 * objects. Function that tests an identity using the given pool of mathematical
 * objects.
 * @param p the pool to which the mathematical object is to be added.
 * @param identity the identity to be verified.
 * @param counter_example a counter example, if it exists, of a test for which
 * the identity does not hold.
 * @return whether the identity holds or not.
 */
bool
__ap_test_identity (__ap_t *            p,
                    char *              identity,
                    __va_assignment_t **counter_example);

/** Function that removes all duplicate mathematical object from a pool.
 * Function that removes all the duplicate mathematical object from the given
 * pool.
 * @param p the pool from which the duplicated mathematical objects will be
 * removed.
 */
void
__ap_remove_duplicates (__ap_t *p);

/** Function that prints the mathematical objects of a pool.
 * Function that prints the mathematical objects of the given pool.
 * @param p the pool whose mathematical objects will be printed.
 * @param print the print function to be used.
 */
void
__ap_print (__ap_t *p);

#endif    // __ABSTRACT_POOL__
