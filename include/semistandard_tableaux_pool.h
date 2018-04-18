#ifndef __SST_POOL__
#define __SST_POOL__

#include <dirent.h>
#include <sys/types.h>

#include "semistandard_tableaux.h"

#define __SST_POOL_DEFAULT_SIZE (1 << 5)


/** Structure that represents a pool of semistandard tableaux.
 * Structure that represents a pool of semistandard tableaux.
 */
typedef struct
{
  size_t size;       //!< true size of the pool.
  size_t counter;    //!< size of the pool.

  __sst_t **tableaux;    //!< entries of the pool.
} __sst_pool_t;

/** Function that generates a random tableaux.
 * Function that generates a random tableaux with the given index.
 * @param idx the index of the tableaux to be randomly generated.
 * @return the generated tableaux.
 */
__sst_t *
__sst_pool_generate_random_tableaux (__tableaux_cell_val_t idx);

/** Creates a pool of semistandard tableaux.
 * Creates a pool of semistandard tableaux.
 * @return the semistandard tableaux pool created.
 */
__sst_pool_t *
__sst_pool_create_sst_pool ();

/** Creates a pool of semistandard tableaux from a bigger pool, where the
 * tableaux have index at most idx. Creates a pool of semistandard tableaux from
 * a bigger pool, where the tableaux have index at most idx.
 * @param p the pool from which the sub-pool will be created.
 * @param idx the maximum index of the tableaux in the new created tableaux
 * pool.
 * @return the semistandard tableaux pool created.
 */
__sst_pool_t *
__sst_pool_create_sst_index_pool (__sst_pool_t *p, __tableaux_cell_val_t idx);

/** Destroys a pool of semistandard tableaux.
 * Destroys a pool of semistandard tableaux.
 * @param p the semistandard tableaux pool to be destroyed.
 */
void
__sst_pool_destroy_sst_pool (__sst_pool_t *p);

/** Function that adds a tableaux to a tableaux pool.
 * Function that adds the given tableaux to the given tableaux pool.
 * @param p the pool to which the tableaux is to be added.
 * @param t the tableaux to be added to the pool.
 */
void
__sst_pool_add_tableaux (__sst_pool_t *p, __sst_t *t);

/** Function that adds a tableaux from a plain file to a tableaux pool.
 * Function that adds the non-shortened tableaux stored in the given filename,
 * to the given tableaux pool.
 * @param p the pool to which the tableaux is to be added.
 * @param fn the filename of the file where the tableaux is stored.
 */
void
__sst_pool_add_tableaux_from_plain_file (__sst_pool_t *p, char *fn);

/** Function that adds a tableaux from a shortened file to a tableaux pool.
 * Function that adds the shortened tableaux stored in the given filename, to
 * the given tableaux pool.
 * @param p the pool to which the tableaux is to be added.
 * @param fn the filename of the file where the shortened tableaux is stored.
 */
void
__sst_pool_add_tableaux_from_compressed_file (__sst_pool_t *p, char *fn);

/** Function that adds all the tableaux that are stored in files within the
 * given directory. Function that adds all the tableaux that are stored in files
 * within the given directory, to the given tableaux pool.
 * @param p the pool to which the tableaux is to be added.
 * @param dir_path the path of the directory where the tableaux are stored.
 */
void
__sst_pool_add_tableaux_from_directory (__sst_pool_t *p, char *dir_path);

/** Function that adds randomly generated tableaux to a tableaux pool.
 * Function that adds nr_random randomly generated tableaux to the given
 * tableaux pool.
 * @param p the pool to which the tableaux are to be added.
 * @param nr_random the number of tableaux to be randomly generated.
 * @param idx the index of the tableaux to be randomly generated.
 */
void
__sst_pool_add_random_tableaux (__sst_pool_t *        p,
                                size_t                nr_random,
                                __tableaux_cell_val_t idx);

/** Function that removes all duplicate tableaux from a pool.
 * Function that removes all the duplicate tableaux from the given pool.
 * @param p the pool from which the duplicated tableaux will be removed.
 */
void
__sst_pool_remove_duplicates (__sst_pool_t *p);

/** Function that prints the tableaux of a pool.
 * Function that prints the tableaux of the given pool.
 * @param p the pool whose tableaux will be printed.
 * @param print the print function to be used.
 */
void
__sst_pool_print (__sst_pool_t *p, void (*print) (const __sst_t *));

#endif    // __SST_POOL__
