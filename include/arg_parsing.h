#ifndef __ARG_PARSING__
#define __ARG_PARSING__

#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

#include "configuration.h"

/*struct argp argp = {
  options,
  parse_opt,
  "",
  "Computes and outputs the mandelbrot set.\v"
  "Be carefull! A 8192x8192 pixel image occupies more than 512 MB!"};*/

int
parse_opt (int key, char *arg, struct argp_state *state);

#endif    // __ARG_PARSING__
