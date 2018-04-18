#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "hashmap.h"
#include "configuration.h"

#ifndef __IDENTITY_TESTING__
#define __IDENTITY_TESTING__

#define __IT_DELIMITER__ "="
#define __IT_OP_SYMBOL__ "."

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
 * @return whether the identity was verified for all the possible combinations
 * with the given elements or not.
 */
bool
__it_test_identity (char *           identity,
                    void *           elems,
                    size_t           nr_elems,
                    identity_testing fn);

#endif    // __IDENTITY_TESTING__
