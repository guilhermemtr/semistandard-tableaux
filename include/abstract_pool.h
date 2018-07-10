#ifndef __ABSTRACT_POOL__
#define __ABSTRACT_POOL__

#include <dirent.h>
#include <sys/types.h>

#include "identity_testing.h"

#define __ABSTRACT_POOL_DEFAULT_SIZE (1 << 5)

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

  void (*multiply) (void *, void *, void **);    //!< multiplies two elements
  bool (*equals) (void *, void *);     //!< checks if two elements are equal
  void (*destroy_element) (void *);    //!< destroys an element
  void (*print_element) (void *);      //!< prints an element
} __abstract_pool_t;

/** Creates a pool of mathematical objects.
 * Creates a pool of mathematical objects.
 * @return the mathematical objects' pool created.
 */
__abstract_pool_t *
__abstract_pool_create_pool ();

/** Destroys a pool of mathematical objects.
 * Destroys a pool of mathematical objects.
 * @param p the mathematical objects pool to be destroyed.
 */
void
__abstract_pool_destroy_pool (__abstract_pool_t *p);

/** Function that adds an element to the pool.
 * Function that adds an element to the pool.
 * @param p the pool to which the element is to be added.
 * @param e the element to be added to the pool.
 */
void
__abstract_pool_add_element (__abstract_pool_t *p, void *e);

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
__abstract_pool_test_identity (__abstract_pool_t * p,
                               char *              identity,
                               __it_assignment_t **counter_example);

/** Function that removes all duplicate mathematical object from a pool.
 * Function that removes all the duplicate mathematical object from the given
 * pool.
 * @param p the pool from which the duplicated mathematical objects will be
 * removed.
 */
void
__abstract_pool_remove_duplicates (__abstract_pool_t *p);

/** Function that prints the mathematical objects of a pool.
 * Function that prints the mathematical objects of the given pool.
 * @param p the pool whose mathematical objects will be printed.
 * @param print the print function to be used.
 */
void
__abstract_pool_print (__abstract_pool_t *p, void (*print) (void *));

#endif    // __ABSTRACT_POOL__
