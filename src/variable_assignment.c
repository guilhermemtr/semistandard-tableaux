#include "variable_assignment.h"

#ifdef __VARIABLE_ASSIGNMENT__

__va_assignment_t *
__va_create_variable_assignment ()
{
  __va_assignment_t *assig = malloc (sizeof (__va_assignment_t));
  assig->size              = __VA_VARIABLE_ASSIGNMENT_DEFAULT_SIZE;
  assig->counter           = 0;
  assig->variables         = malloc (assig->size * sizeof (char *));
  assig->entries           = malloc (assig->size * sizeof (size_t));
  return assig;
}

static void
__va_resize_to (__va_assignment_t *assig, size_t sz)
{
  if (assig->counter > sz)
  {
    sz = assig->counter;
  }

  assig->size      = sz;
  assig->variables = realloc (assig->variables, assig->size * sizeof (char *));
  assig->entries   = realloc (assig->entries, assig->size * sizeof (size_t));
}

void
__va_add_variable_assignment (__va_assignment_t *_va_a, char *var, size_t idx)
{
  if (_va_a->counter == _va_a->size)
  {
    __va_resize_to (_va_a, (_va_a->size + 1) << 1);
  }

  char *str = malloc ((1 + strlen (var)) * sizeof (char));
  strcpy (str, var);

  _va_a->variables[_va_a->counter] = str;
  _va_a->entries[_va_a->counter++] = idx;
}

void
__va_destroy_variable_assignment (__va_assignment_t *_va_a)
{
  for (size_t i = 0; i < _va_a->counter; i++)
  {
    free (_va_a->variables[i]);
  }

  free (_va_a->entries);
  free (_va_a->variables);
  free (_va_a);
}

#endif    // __VARIABLE_ASSIGNMENT__
