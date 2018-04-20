#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hashmap.h"
#include "configuration.h"

#ifndef __IDENTITY_TESTING__
#define __IDENTITY_TESTING__

#define __IT_DELIMITER__ "="
#define __IT_OP_SYMBOL__ "."

#define __IT_VARIABLE_ASSIGNMENT_DEFAULT_SIZE (1 << 5)

/** Verifies the validity of an identity, given two assignments.
 * Verifies the validity of an identity, given two assignments and the identity.
 * @param x the left side of the identity.
 * @param len_x the length of the left side of the identity.
 * @param y the right side of the identity.
 * @param len_y the length of the right side of the identity.
 * @param assigns the assignments to the variables.
 * @param nr_vars the number of variables.
 * @param elems the domains of the variables.
 * @return whether the identity was verified for the given assignment or not.
 */
typedef bool(identity_testing) (size_t *x,
                                size_t  len_x,
                                size_t *y,
                                size_t  len_y,
                                size_t *assigns,
                                size_t  nr_vars,
                                void *  elems);

/** Structure that represents a variable assignment.
 * Structure that represents a variable assignment.
 */
typedef struct
{
  size_t  size;         //!< true size of the pool.
  size_t  counter;      //!< size of the pool.
  char ** variables;    //!< names of the variables.
  size_t *entries;      //!< entries of the pool.
} __it_assignment_t;

/** Creates a new variable assignment structure.
 * Creates a new variable assignment structure.
 * @return the new variable assignment structure.
 */
__it_assignment_t *
__it_create_variable_assignment ();

/** Assigns a value to a variable in a assignment structure.
 * Assigns a value to a variable in a assignment structure.
 * @param _it_a the variable assignment structure.
 * @param var the name of the variable.
 * @param idx the index of the assignment's value.
 */
void
__it_add_variable_assignment (__it_assignment_t *_it_a, char *var, size_t idx);

/** Destroys a variable assignment structure.
 * Destroys a variable assignment structure.
 * @param _it_a the variable assignment structure.
 */
void
__it_destroy_variable_assignment (__it_assignment_t *_it_a);


/** Tests the validity of the given identity.
 * Tests the validity of the given identity, by trying all possible combinations
 * of the given elements, and verifying if the identity holds for those
 * combinations.
 * @param identity the identity to be verified, a string of the form
 * "a1.a2...=b1.b2...".
 * @param elems the elements to which the variables can be set.
 * @param nr_elems the number of elements to which the variables can be set.
 * @param fn the function used to test the identity for each possible variable
 * assignments.
 * @param counter_example a counter example for why the identity does not hold.
 * If the identity holds for all tests, then counter_example is left unchanged.
 * @return whether the identity was verified for all the possible combinations
 * with the given elements or not.
 */
bool
__it_test_identity (char *              identity,
                    void *              elems,
                    size_t              nr_elems,
                    identity_testing    fn,
                    __it_assignment_t **counter_example);

#endif    // __IDENTITY_TESTING__
