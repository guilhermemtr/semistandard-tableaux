#include "arg_parsing.h"

const char* argp_program_bug_address = MAIL_ADDRESS;
const char* argp_program_version     = VERSION;

extern struct argp_option options[];
extern struct argp argp;

int
parse_opt (int key, char *arg, struct argp_state *state)
{
  printf ("HELLO\n");
  return 0;
}
