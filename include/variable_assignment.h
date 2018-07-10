#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef __VARIABLE_ASSIGNMENT__
#define __VARIABLE_ASSIGNMENT__

#define __VA_VARIABLE_ASSIGNMENT_DEFAULT_SIZE (1 << 5)


/** Structure that represents a variable assignment.
 * Structure that represents a variable assignment.
 */
typedef struct
{
  size_t  size;         //!< true size of the pool.
  size_t  counter;      //!< size of the pool.
  char ** variables;    //!< names of the variables.
  size_t *entries;      //!< entries of the pool.
} __va_assignment_t;

/** Creates a new variable assignment structure.
 * Creates a new variable assignment structure.
 * @return the new variable assignment structure.
 */
__va_assignment_t *
__va_create_variable_assignment ();

/** Assigns a value to a variable in a assignment structure.
 * Assigns a value to a variable in a assignment structure.
 * @param _va_a the variable assignment structure.
 * @param var the name of the variable.
 * @param idx the index of the assignment's value.
 */
void
__va_add_variable_assignment (__va_assignment_t *_va_a, char *var, size_t idx);

/** Destroys a variable assignment structure.
 * Destroys a variable assignment structure.
 * @param _va_a the variable assignment structure.
 */
void
__va_destroy_variable_assignment (__va_assignment_t *_it_a);

#endif    // __VARIABLE_ASSIGNMENT__
