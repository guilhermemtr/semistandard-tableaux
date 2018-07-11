#ifndef __TM_POOL__
#define __TM_POOL__

#include <dirent.h>
#include <sys/types.h>

#include "utils.h"
#include "tropical_matrix.h"
#include "abstract_pool.h"


/** Structure that represents a pool of tropical matrices.
 * Structure that represents a pool of tropical matrices.
 */
typedef struct
{
  __ap_t *pool;    //!< the pool.
} __tm_pool_t;

/** Creates a pool of tropical matrices.
 * Creates a pool of tropical matrices.
 * @return the tropical matrices pool created.
 */
__tm_pool_t *
__tm_pool_create_tm_pool ();

/** Destroys a pool of tropical matrices.
 * Destroys a pool of tropical matrices.
 * @param p the tropical matrices pool to be destroyed.
 */
void
__tm_pool_destroy_tm_pool (__tm_pool_t *p);

/** Function that adds a tropical matrix to a tropical matrices pool.
 * Function that adds the given tropical matrix to the given tropical matrices
 * pool.
 * @param p the pool to which the matrix is to be added.
 * @param t the matrix to be added to the pool.
 */
void
__tm_pool_add_tropical_matrix (__tm_pool_t *p, __tm_t *t);

/** Function that tests an identity using the given pool of tropical matrices.
 * Function that tests an identity using the given pool of tropical matrices.
 * @param p the pool of tropical matrices.
 * @param identity the identity to be verified.
 * @param counter_example a counter example, if it exists, of a test for which
 * the identity does not hold.
 * @return whether the identity holds or not.
 */
bool
__tm_pool_test_identity (__tm_pool_t *       p,
                         char *              identity,
                         __va_assignment_t **counter_example);

/** Function that adds a tropical matrix from a plain file to a tropical
 * matrices pool. Function that adds the tropical matrix stored in the given
 * filename, to the given tropical matrices pool.
 * @param p the pool to which the tropical matrix is to be added.
 * @param fn the filename of the file where the tropical matrix is stored.
 */
void
__tm_pool_add_matrix_from_plain_file (__tm_pool_t *p, char *fn);

/** Function that adds all the tropical matrices that are stored in files within
 * the given directory. Function that adds all the tropical matrices that are
 * stored in files within the given directory, to the given tropical matrices
 * pool.
 * @param p the pool to which the tropical matrix is to be added.
 * @param dir_path the path of the directory where the tropical matrices are
 * stored.
 */
void
__tm_pool_add_matrices_from_directory (__tm_pool_t *p, char *dir_path);

/** Function that removes all duplicate tropical matrices from a pool.
 * Function that removes all the duplicate tropical matrices from the given
 * pool.
 * @param p the pool from which the duplicated tropical matrices will be
 * removed.
 */
void
__tm_pool_remove_duplicates (__tm_pool_t *p);

/** Function that prints the tropical matrices of a pool.
 * Function that prints the tropical matrices of the given pool.
 * @param p the pool whose tropical matrices will be printed.
 * @param print the print function to be used.
 */
void
__tm_pool_print (__tm_pool_t *p);

/** Function that prints the tropical matrices of a pool.
 * Function that prints the tropical matrices of the given pool.
 * @param p the pool whose tropical matrices will be printed.
 * @param print the print function to be used.
 */
void
__tm_pool_custom_print (__tm_pool_t *p, void (*print) (const __tm_t *));

#endif    // __TM_POOL__
