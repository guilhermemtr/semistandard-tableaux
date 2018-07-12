#include "types.h"


#ifdef __SST_TYPES__

static const char *structure_type_string[] = {
  FOREACH_STRUCTURE_TYPE (GENERATE_STRING)};

const char *
get_structure_type_string (enum structure_type t)
{
  return structure_type_string[t];
}



#endif    // __SST_TYPES__
